#include "common.h"

extern int current_sreg;

uint32_t dram_read(hwaddr_t addr, size_t len);
void dram_write(hwaddr_t addr, size_t len, uint32_t data);
uint32_t cache_read_L1(hwaddr_t addr,size_t len);
void cache_write_L1(hwaddr_t addr, size_t len, uint32_t data);
void load_cache_L1(hwaddr_t addr);
/*lnaddr_t segment_translate(hwaddr_t addr,size_t len,int current_sreg);

lnaddr_t segment_translate(hwaddr_t addr,size_t len,int current_sreg){
	return 0;
}*/

/* Memory accessing interfaces */

uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
//    return cache_read_L1(addr,len);
    return dram_read(addr,len);
}

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
//    cache_write_L1(addr,len,data);
    dram_write(addr,len,data);
}

uint32_t lnaddr_read(lnaddr_t addr,size_t len){
	assert(len == 1 || len == 2 || len == 4);
	return hwaddr_read(addr,len);
}

void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	hwaddr_write(addr,len,data);
}

uint32_t swaddr_read(swaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
//	lnaddr_t lnaddr=segment_translate(addr,len,current_sreg);
//	return lnaddr_read(lnaddr, len);
    return hwaddr_read(addr,len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
//	lnaddr_t lnaddr=segment_translate(addr,len,current_sreg);
//	lnaddr_write(lnaddr, len, data);
    hwaddr_write(addr,len,data);
}

uint32_t hwaddr_read_instr(hwaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
//    return cache_read_L1(addr,len);
    return dram_read(addr,len);
}

uint32_t instr_fetch(swaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	current_sreg=1;
//	lnaddr_t lnaddr=segment_translate(addr,len,current_sreg);
//	return lnaddr_read(lnaddr,len);
    return hwaddr_read(addr,len);
}

