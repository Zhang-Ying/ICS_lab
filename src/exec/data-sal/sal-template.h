#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(sal_rm21_,SUFFIX)){
	ModR_M n;
	char t;
	n.val=instr_fetch(eip+1,1);
	DATA_TYPE result;
 	if(n.mod==3){ 
		DATA_TYPE m=REG(n.reg);
		result=m<<1;
		t=result&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if(m==0)
			cpu.eflags.ZF=0;
		else 
			cpu.eflags.ZF=1;
		if(m>=0x80000000)
			cpu.eflags.CF=1;
		else
			cpu.eflags.CF=0;
		if((m>0&&result<0)||(m<0&&result>0))
				cpu.eflags.OF=1;
		else
		        cpu.eflags.OF=0;
		if(result<0)
		    cpu.eflags.SF=1;
		else
		    cpu.eflags.SF=0;
		REG(n.reg)=result;
		print_asm("sal" str(SUFFIX) " 0x%x,%%%s",1,REG_NAME(n.reg));
		return 1+1;
	}
 	else { 
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE imm=swaddr_read(addr,4);
		result=imm<<1;
		MEM_W(addr,result);
		t=result&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if(imm==0)
			cpu.eflags.ZF=0;
		else
			cpu.eflags.ZF=1;
		if(imm>=0x80000000)
			cpu.eflags.CF=1;
		else
			cpu.eflags.CF=0;
		if((imm<0&&result>0)||(imm>0&&result<0))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		print_asm("sal" str(SUFFIX) " 0x%x,%s",1,ModR_M_asm);
		return 1+len;
 	} 
}
make_helper(concat(sar_rm21_,SUFFIX)){
	ModR_M n;
	char t;
	n.val=instr_fetch(eip+1,1);
	DATA_TYPE result;
	if (n.mod==3){
		DATA_TYPE m=REG(n.reg);
		result=m>>1;
		REG(n.reg)=result;
		t=result&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if((m<<31)==0)
			cpu.eflags.CF=0;
		else
			cpu.eflags.CF=1;
		if(m==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		print_asm("sar" str(SUFFIX) " 0x%x,%%%s",1,REG_NAME(n.reg));
		return 1+1;
  	}     
	else{ 
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE m=swaddr_read(addr,4);
		result=m>>1;
		t=result&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		MEM_W(addr,result);
		if((m<<31)==0)
			cpu.eflags.CF=0;
		else
			cpu.eflags.CF=1;
		if(m==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		print_asm("sar" str(SUFFIX) " 0x%x,%s",1,ModR_M_asm);
		return 1+len;
  	}
}
make_helper(concat(shr_rm21_,SUFFIX)){
	ModR_M n;
	char t;
	n.val=instr_fetch(eip+1,1);
	DATA_TYPE_S result;
	if(n.mod==3){ 
		DATA_TYPE_S m=REG(n.reg);
		result=(m>>1);
		REG(n.reg)=result;
		t=result&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if((m<<31)==0)
			cpu.eflags.CF=0;
		else
			cpu.eflags.CF=1;
		if(m==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		print_asm("shr" str(SUFFIX) " 0x%x,%%%s",1,REG_NAME(n.reg));
		return 1+1;
  	} 
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE_S m=swaddr_read(addr,4);
		result=m>>1;
		MEM_W(addr,result);
		t=result&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if((m<<31)==0)
			cpu.eflags.CF=0;
		else
			cpu.eflags.CF=1;
		if(m==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		print_asm("shr" str(SUFFIX) " 0x%x,%s",1,ModR_M_asm);
		return 1+len;
  	} 
}
make_helper(concat(sal_rm2cl_,SUFFIX)){
	ModR_M n;
	char t;
	n.val=instr_fetch(eip+1,1);
	DATA_TYPE result;
 	if(n.mod==3){ 
		DATA_TYPE m=REG(n.reg);
		result=m<<REG(n.R_M);
		REG(n.reg)=result;
		t=result&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if((m<<31)==0)
			cpu.eflags.CF=0;
		else
			cpu.eflags.CF=1;
		if(m==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		print_asm("sal" str(SUFFIX) " %%%s,%%%s",REG_NAME(n.reg),REG_NAME(n.R_M));
		return 1+1;
	} 
  	else{ 
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE m=swaddr_read(addr,4);
		result=m<<REG(n.reg);
		MEM_W(addr,result);
		t=result&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if((m<<31)==0)
			cpu.eflags.CF=0;
		else
			cpu.eflags.CF=1;
		if(m==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		print_asm("sal" str(SUFFIX) " %%%s,%s",REG_NAME(n.reg),ModR_M_asm);
		return 1+len;
	} 
}
make_helper(concat(sar_rm2cl_,SUFFIX)){
	ModR_M n;
	n.val=instr_fetch(eip+1,1);
	DATA_TYPE result;
	char t;
 	if(n.mod==3){
		DATA_TYPE m=REG(n.reg);
		result=m>>REG(n.R_M);
		REG(n.reg)=result;
		t=result&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if((m<<31)==0)
			cpu.eflags.CF=0;
		else
			cpu.eflags.CF=1;
		if(m==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		print_asm("sar" str(SUFFIX) " %%%s,%%%s",REG_NAME(n.R_M),REG_NAME(n.reg));
		return 1+1;
	} 
	else{ 
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE m=swaddr_read(addr,4);
		result=m>>REG(n.reg);
		MEM_W(addr,result);
		t=result&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if((m<<31)==0)
			cpu.eflags.CF=0;
		else
			cpu.eflags.CF=1;
		if(m==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		print_asm("sar" str(SUFFIX) " %%%s,%s",REG_NAME(n.reg),ModR_M_asm);
		return 1+len;
  	}
}
make_helper(concat(shr_rm2cl_,SUFFIX)){
	ModR_M n;
	n.val=instr_fetch(eip+1,1);
	DATA_TYPE_S result;
	char t;
	if(n.mod== 3){
		DATA_TYPE_S m=REG(n.reg);
		result=m>>REG(n.R_M);
		REG(n.reg)=result;
		t=result&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if((m<<31)==0)
			cpu.eflags.CF=0;
		else
			cpu.eflags.CF=1;
		if(m==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		print_asm("shr" str(SUFFIX) " %%%s,%%%s",REG_NAME(n.R_M),REG_NAME(n.reg));
		return 1+1;
 	}   
	else{ 
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE_S m=swaddr_read(addr,4);
		result=m>>REG(n.reg);
		MEM_W(addr,result);
		t=result&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if((m<<31)==0)
			cpu.eflags.CF=0;
		else
			cpu.eflags.CF=1;
		if(m==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		print_asm("shr" str(SUFFIX) " %%%s,%s",REG_NAME(n.reg),ModR_M_asm);
		return 1+len;
  	}  
}
make_helper(concat(sal_rm2i_,SUFFIX)){
	ModR_M n;
	n.val=instr_fetch(eip+1,1);
	DATA_TYPE result;
	char t;
	if( n.mod==3){ 
		DATA_TYPE m=REG(n.R_M);
		DATA_TYPE imm=instr_fetch(eip+1+1,1);
		result=m<<imm;
		REG(n.R_M)=result;
		t=result&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if((m<<31)==0)
			cpu.eflags.CF=0;
		else
			cpu.eflags.CF=1;
		if(m==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;																									
		print_asm("sal" str(SUFFIX) " 0x%x,%%%s",imm,REG_NAME(n.R_M));
		return 1+1+1;					
	} 
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE m=swaddr_read(addr,4);
		DATA_TYPE imm1=instr_fetch(eip+1+len,1);
		result=m<<imm1;
		MEM_W(addr,result);
		t=result&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if((m<<31)==0)
			cpu.eflags.CF=0;
		else
			cpu.eflags.CF=1;
		if(m==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		print_asm("sal" str(SUFFIX) " 0x%x,%s",imm1,ModR_M_asm);
		return 1+len;
  	}  
} 
make_helper(concat(sar_rm2i_,SUFFIX)){
	ModR_M n;
	n.val=instr_fetch(eip+1,1);
	DATA_TYPE result;
	char t;
	if(n.mod==3){ 
		DATA_TYPE m=REG(n.R_M);
		DATA_TYPE imm=instr_fetch(eip+1+1,1);
		result=m>>imm;
		REG(n.R_M)=result;
		t=result&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if((m<<31)==0)
			cpu.eflags.CF=0;																				
		else						
			cpu.eflags.CF=1;
		if(m==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		print_asm("sar" str(SUFFIX) " 0x%x,%%%s",imm,REG_NAME(n.R_M));
		return 1+1+1;
 	} 
 	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE m=swaddr_read(addr,4);
		DATA_TYPE imm1=instr_fetch(eip+1+len,DATA_BYTE);
		result=m>>imm1;
		MEM_W(addr,result);
		t=result&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if((m<<31)==0)
			cpu.eflags.CF=0;										
		else																				
			cpu.eflags.CF=1;								
		if(m==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		print_asm("sar" str(SUFFIX) " 0x%x,%s",imm1,ModR_M_asm);
		return 1+len;
	}  
}
make_helper(concat(shr_rm2i_,SUFFIX)){
	ModR_M n;			     
 	n.val=instr_fetch(eip+1,1);
	DATA_TYPE_S result;
	char t;
	if(n.mod==3){
		DATA_TYPE_S m=REG(n.R_M);
		DATA_TYPE_S imm=instr_fetch(eip+1,1);
		result=m>>imm;
		REG(n.R_M)=result;
		t=result&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if((m<<31)==0)
			cpu.eflags.CF=0;
		else
			cpu.eflags.CF=1;
		if(m==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		print_asm("shr" str(SUFFIX) " 0x%x,%%%s",imm,REG_NAME(n.R_M));
		return 1+1+1;
 	} 
	else{  
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE_S m=swaddr_read(addr,4);
		DATA_TYPE_S imm1=instr_fetch(eip+1+len,DATA_BYTE);
		result=m>>imm1;
		MEM_W(addr,result);
		t=result&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if((m<<31)==0)
			cpu.eflags.CF=0;
		else
			cpu.eflags.CF=1;
		if(m==0)										
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		print_asm("shr" str(SUFFIX) " 0x%x,%s",imm1,ModR_M_asm);
		return 1+len;
  	} 
}
#include "exec/template-end.h"


