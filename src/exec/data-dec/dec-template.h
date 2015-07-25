#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(dec_r_,SUFFIX)){
	int regcode;
	char t;
	regcode=instr_fetch(eip,1);
	regcode=regcode&0x7;
	DATA_TYPE s=REG(regcode);
	REG(regcode)=REG(regcode)-1;
	if(s<1){
		cpu.eflags.CF=1;
		cpu.eflags.SF=1;
	}
	else{
		cpu.eflags.CF=0;
		cpu.eflags.SF=0;
	}
	if(REG(regcode)==0)
		cpu.eflags.ZF=1;
	else
		cpu.eflags.ZF=0;
	if(s<0&&REG(regcode)>0)
		cpu.eflags.OF=1;
	else
		cpu.eflags.OF=0;
	t=REG(regcode)&0xff;
	t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
	cpu.eflags.PF=t&0x01;
	print_asm("dec" str(SUFFIX) " %%%s",REG_NAME(regcode));
	return 1;
}

#include "exec/template-end.h"
