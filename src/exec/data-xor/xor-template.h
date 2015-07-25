#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(xor_rm2r_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	DATA_TYPE s;
	long result;
	char t;
	if(m.mod==3){
		REG(m.R_M)=REG(m.R_M)^REG(m.reg);
		s=REG(m.R_M)^REG(m.reg);
		result=REG(m.R_M)^REG(m.reg);
		t=s&0xff;
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
		print_asm("xor" str(SUFFIX) " %%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE imm1=MEM_R(addr);
		MEM_W(addr,imm1^REG(m.reg));
		s=imm1^REG(m.reg);
		result=imm1^REG(m.reg);
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
		print_asm("xor" str(SUFFIX) " %%%s,%s",REG_NAME(m.reg),ModR_M_asm);
		return 1+len;
	}
}
make_helper(concat(xor_r2rm_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	DATA_TYPE s;
	long result;
	char t;
	if(m.mod==3){
		REG(m.reg)=REG(m.R_M)^REG(m.reg);
		s=REG(m.R_M)^REG(m.reg);
		result=REG(m.R_M)^REG(m.reg);
		t=s&0xff;
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
		print_asm("xor" str(SUFFIX) " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
		return 1+1;
	} 
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE imm1=MEM_R(addr);
		REG(m.reg)=imm1^REG(m.reg);
		s=imm1^REG(m.reg);
		result=imm1^REG(m.reg);
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
		print_asm("xor" str(SUFFIX) " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));
		return 1+len;
	}
}
make_helper(concat(xor_al_,SUFFIX)){
	DATA_TYPE s;
	long result;
	char t;
	DATA_TYPE imm=instr_fetch(eip+1,DATA_BYTE);
	REG(0)=REG(0)^imm;
	s=REG(0)^imm;
	result=REG(0)^imm;
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
	print_asm("xor" str(SUFFIX) " 0x%x,%%%s",imm,REG_NAME(0));
	return 1+DATA_BYTE;
}

#include "exec/template-end.h"
