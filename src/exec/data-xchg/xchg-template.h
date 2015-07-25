#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(xchg_ax2r_,SUFFIX)){
	char m=instr_fetch(eip,1);
	int regcode=m&0x7;
	if(regcode!=0){
		DATA_TYPE temp;
		temp=REG(regcode);
		REG(regcode)=REG(0);
		REG(0)=temp;
		print_asm("xchg" str(SUFFIX) " %%%s,%%%s",REG_NAME(regcode),REG_NAME(0));
		return 1+1+1;
	}
	else{
		print_asm("nop");
		return 1;
	}
}
make_helper(concat(xchg_rm2r_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	if(m.mod==3){
		DATA_TYPE temp;
		temp=REG(m.reg);
		REG(m.reg)=REG(m.R_M);
		REG(m.R_M)=temp;
		print_asm("xchg" str(SUFFIX) " %%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));
		return 1+1+1+1;
	} 
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE temp;
		temp=REG(m.reg);
		REG(m.reg)=swaddr_read(addr,DATA_BYTE);
		swaddr_write(addr,DATA_BYTE,temp);
		print_asm("xchg" str(SUFFIX) " %%%s,%s",REG_NAME(m.reg),ModR_M_asm);
		return 1+1+len;
	}
}

#include "exec/template-end.h"
