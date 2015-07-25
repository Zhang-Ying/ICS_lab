#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(and_rm2r_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	DATA_TYPE result;
	cpu.eflags.OF=0;
	cpu.eflags.CF=0;
	if(m.mod==3){
		int regcode=instr_fetch(eip+1+1,1);
		result=REG(m.R_M)&REG(regcode);
		REG(m.R_M)=result;
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(result==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		print_asm("and" str(SUFFIX) " %%%s,%%%s",REG_NAME(regcode),REG_NAME(m.R_M));
		return 1+1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1+1,&addr);
		DATA_TYPE imm;
		imm=swaddr_read(addr,DATA_BYTE);
		result=imm&REG(m.R_M);
		MEM_W(addr,result);
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(result==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		print_asm("and" str(SUFFIX) " %s,%%%s",ModR_M_asm,REG_NAME(m.R_M));
		return 1+1+len;
	}
}
make_helper(concat(and_r2rm_,SUFFIX)){
	int regcode=instr_fetch(eip+1,1);
	DATA_TYPE imm=REG(regcode);
	cpu.eflags.OF=0;
	cpu.eflags.CF=0;
	DATA_TYPE result;
	ModR_M m;
	m.val=instr_fetch(eip+1+1,1);
	if(m.mod==3){
		result=imm&REG(m.R_M);
		REG(regcode)=result;
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(result==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		print_asm("and" str(SUFFIX) " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(regcode));
		return 1+1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1+1,&addr);
		DATA_TYPE imm1=swaddr_read(addr,DATA_BYTE);
		result=imm&imm1;
		REG(regcode)=result;
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(result==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		print_asm("and" str(SUFFIX) " %s,%%%s",ModR_M_asm,REG_NAME(regcode));
		return 1+len+1;
	}
}
make_helper(concat(and_al_,SUFFIX)){
	DATA_TYPE imm=instr_fetch(eip+1,DATA_BYTE);
	DATA_TYPE result;
	result=REG(0)&imm;
	REG(0)=result;
	cpu.eflags.CF=0;
	cpu.eflags.OF=0;
	if(result<0)
		cpu.eflags.SF=1;
	else
		cpu.eflags.SF=0;
	if(result==0)
		cpu.eflags.ZF=1;
	else
		cpu.eflags.ZF=0;
	print_asm("and" str(SUFFIX) " 0x%x,%%%s",imm,REG_NAME(0));
	return 1+1;
}
#include "exec/template-end.h"
