#include "common.h"
#include "lib/misc.h"
#include <stdlib.h>

/*This is my cache design*/


uint32_t dram_read(hwaddr_t addr, size_t len);
void dram_write(hwaddr_t addr, size_t len, uint32_t data);

#define CACHE_BYTE 22
#define CACHE_BLOCK_BYTE 6
#define INDEX (CACHE_BYTE-CACHE_BLOCK_BYTE-4)
#define BLOCK_OFFSET CACHE_BLOCK_BYTE
#define TAG (32-INDEX-BLOCK_OFFSET)

typedef struct{
	bool valid;
	bool dirty;
	uint32_t tag : TAG;
	uint32_t data[1<<BLOCK_OFFSET];
}CC;

#define GROUP_INDEX (1<<INDEX)
#define WAYS 16

CC cachemem[GROUP_INDEX][WAYS];

void load_cache_L2(hwaddr_t addr){
	uint32_t gi;
	uint32_t t;
	uint32_t count;
	int i;
	gi=(addr&0x1ffc0)>>6;
	t=(addr&0xfffc0000)>>18;
	for(count=0;count<WAYS;count++)
		if(cachemem[gi][count].valid==0)
			break;
	if(count==WAYS&&cachemem[gi][count-1].valid==1)
		count=rand()%WAYS;
	cachemem[gi][count].tag=t;
	cachemem[gi][count].valid=1;
	cachemem[gi][count].dirty=0;
	for(i=0;i<(1<<BLOCK_OFFSET);i++){
		cachemem[gi][count].data[i]=dram_read((addr&0xffffffc0)+i,1);
	}
}

uint32_t cache_read_L2(hwaddr_t addr,size_t len){
	uint32_t gi;
	uint32_t t;
	uint32_t off;
	uint32_t count;
	gi=(addr&0x1ffc0)>>6;										
	t=(addr&0xfffc0000)>>18;	
	off=addr&0x3f;			
	if(len==2&&off==(1<<BLOCK_OFFSET)-1)
		return cache_read_L2(addr,1)+(cache_read_L2(addr+1,1)<<8);
	else if(len==4&&off==(1<<BLOCK_OFFSET)-1)
			return cache_read_L2(addr,1)+(cache_read_L2(addr+1,2)<<8)+(cache_read_L2(addr+3,1)<<24);
	else if(len==4&&off==(1<<BLOCK_OFFSET)-2)
		return cache_read_L2(addr,2)+(cache_read_L2(addr+2,2)<<16);
	else if(len==4&&off==(1<<BLOCK_OFFSET)-3)
		return cache_read_L2(addr,2)+(cache_read_L2(addr+2,1)<<16)+(cache_read_L2(addr+3,1)<<24);
	else{
		for(count=0;count<WAYS;count++){
			if(cachemem[gi][count].valid==1&&cachemem[gi][count].tag==t){
				if(len==1)
					return cachemem[gi][count].data[off];
				else if(len==2)
					return cachemem[gi][count].data[off]+(cachemem[gi][count].data[off+1]<<8);
				else
					return cachemem[gi][count].data[off]+(cachemem[gi][count].data[off+1]<<8)+(cachemem[gi][count].data[off+2]<<16)+(cachemem[gi][count].data[off+3]<<24);
			}
		}
		load_cache_L2(addr);
		return dram_read(addr,len);
	}
}

void cache_write_L2(hwaddr_t addr, size_t len, uint32_t data){
	uint32_t gi;
	uint32_t t;
	uint32_t off;
	uint32_t count;
	gi=(addr&0x1ffc0)>>6;
	t=(addr&0xfffc0000)>>18;
	off=addr&0x3f;
	if(len==2&&off==(1<<BLOCK_OFFSET)-1){
		cache_write_L2(addr,1,(data&0xff00)>>8);
		cache_write_L2(addr+1,1,data&0xff);
	}
	else if(len==4&&off==(1<<BLOCK_OFFSET)-1){
		cache_write_L2(addr,1,(data&0xff000000)>>24);
		cache_write_L2(addr+1,2,(data&0xffff00)>>8);
		cache_write_L2(addr+3,1,data&0xff);
	}
	else if(len==4&&off==(1<<BLOCK_OFFSET)-2){
		cache_write_L2(addr,2,(data&0xffff0000)>>16);
		cache_write_L2(addr+2,2,data&0xffff);																					
	}
	else if(len==4&&off==(1<<BLOCK_OFFSET)-3){
		cache_write_L2(addr,2,(data&0xffff0000)>>16);
		cache_write_L2(addr+2,1,(data&0xff00)>>8);
		cache_write_L2(addr+3,1,data&0xff);
	}
	else{
		for(count=0;count<WAYS;count++){
			if(cachemem[gi][count].valid==1&&cachemem[gi][count].tag==t){
				if(len==1)
					cachemem[gi][count].data[off]=data;
				else if(len==2){
					cachemem[gi][count].data[off]=data&0xff;
					cachemem[gi][count].data[off+1]=(data&0xff00)>>8;
				}
				else{
					cachemem[gi][count].data[off]=data&0xff;
					cachemem[gi][count].data[off+1]=(data&0xff00)>>8;
					cachemem[gi][count].data[off+2]=(data&0xff0000)>>16;
					cachemem[gi][count].data[off+3]=(data&0xff000000)>>24;
				}
				cachemem[gi][count].dirty=1;
				dram_write(addr,len,data);
				goto L1;
			}
		}
		dram_write(addr,len,data);
		load_cache_L2(addr);
L1:     ;
	}
}

void init_cache_L2(){
	int i;
	int j;
	for(i=0;i<GROUP_INDEX;i++)
		for(j=0;j<WAYS;j++)
			cachemem[i][j].valid=0;
}

