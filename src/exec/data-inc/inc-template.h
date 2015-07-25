#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(inc_r_,SUFFIX)){
	int regcode;
	char m;
	DATA_TYPE s;
	long result;
	char t;
	m=instr_fetch(eip+1,1);
	regcode=m&0x7;
	REG(regcode)+=1;
	s=REG(regcode);
	result=REG(regcode);
	t=s&0xff;
	t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
	cpu.eflags.PF=t&0x01;
	if(result==s+0x100000000)
		cpu.eflags.CF=1;
	else
		cpu.eflags.CF=0;
	if(cpu.eflags.CF==1)
		cpu.eflags.SF=1;
	else if(s<0)
		cpu.eflags.SF=1;
	else
		cpu.eflags.SF=0;
	if(cpu.eflags.CF==0&&s==0)
		cpu.eflags.ZF=1;
	else
		cpu.eflags.ZF=0;
	if(cpu.eflags.CF==1)
		cpu.eflags.OF=0;
	else if(result!=s+0x100000000)
		cpu.eflags.OF=1;
	else
		cpu.eflags.OF=0;
	print_asm("inc" str(SUFFIX) " %%%s",REG_NAME(regcode));
	return 1+1;
}
make_helper(concat(inc_rm_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	DATA_TYPE s;
	long result;
	char t;
	if(m.mod==3){
		REG(m.R_M)+=1;
		s=REG(m.R_M);
		result=REG(m.R_M);
        t=s&0xff;
        t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
        cpu.eflags.PF=t&0x01;
        if(result==s+0x100000000)
	                cpu.eflags.CF=1;
        else
	                cpu.eflags.CF=0;
        if(cpu.eflags.CF==1)
	                cpu.eflags.SF=1;
        else if(s<0)
	                cpu.eflags.SF=1;
        else
	                cpu.eflags.SF=0;
        if(cpu.eflags.CF==0&&s==0)
	                cpu.eflags.ZF=1;
        else
	                cpu.eflags.ZF=0;
        if(cpu.eflags.CF==1)
	                cpu.eflags.OF=0;
        else if(result!=s+0x100000000)
	                cpu.eflags.OF=1;
        else
	                cpu.eflags.OF=0;
		print_asm("inc" str(SUFFIX) " %%%s",REG_NAME(m.R_M));
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		MEM_W(addr,MEM_R(addr)+1);
		s=MEM_R(addr);
		result=MEM_R(addr);
        t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if(result==s+0x100000000)
			cpu.eflags.CF=1;
		else
			cpu.eflags.CF=0;
		if(cpu.eflags.CF==1)
			cpu.eflags.SF=1;
		else if(s<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(cpu.eflags.CF==0&&s==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(cpu.eflags.CF==1)
			cpu.eflags.OF=0;
		else if(result!=s+0x100000000)
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		print_asm("inc" str(SUFFIX) " %s",ModR_M_asm);
		return 1+len;
	}
}

#include "exec/template-end.h"

#include "exec/template-end.h"
