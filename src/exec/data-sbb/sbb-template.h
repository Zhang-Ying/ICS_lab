#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(sbb_rm2r_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	DATA_TYPE s;
	long result;
	char t;
	if(m.mod==3){
		s=REG(m.R_M)-REG(m.reg)-cpu.eflags.CF;
		result=REG(m.R_M)-REG(m.reg)-cpu.eflags.CF;																			
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
		REG(m.R_M)=s;
		print_asm("sbb" str(SUFFIX) " %%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE n=instr_fetch(eip+1+len,DATA_BYTE);
		s=REG(m.reg)-n-cpu.eflags.CF;
		result=REG(m.reg)-n-cpu.eflags.CF;
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
		MEM_W(addr,s);
		print_asm("sbb" str(SUFFIX) " %%%s,%s",REG_NAME(m.reg),ModR_M_asm);
		return 1+len;
	}
}
make_helper(concat(sbb_r2rm_,SUFFIX)){
	int regcode=instr_fetch(eip+1,1);
	ModR_M m;
	m.val=instr_fetch(eip+1+1,1);
	DATA_TYPE s;
	long result;
	char t;
	if(m.mod==3){
		s=REG(regcode)-REG(m.R_M)-cpu.eflags.CF;
		result=REG(regcode)-REG(m.R_M)-cpu.eflags.CF;
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
		REG(regcode)=s;
		print_asm("sbb" str(SUFFIX) " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(regcode));
		return 1+1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1+1,&addr);
		DATA_TYPE n=instr_fetch(eip+1+1+len,DATA_BYTE);
		s=REG(regcode)-n-cpu.eflags.CF;
		result=REG(regcode)-n-cpu.eflags.CF;
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
		REG(regcode)=s;
		print_asm("sbb" str(SUFFIX) " %s,%%%s",ModR_M_asm,REG_NAME(regcode));
		return 1+1+len;
	}
}
make_helper(concat(sbb_al_,SUFFIX)){
	DATA_TYPE imm=instr_fetch(eip+1,1);
	DATA_TYPE m=REG(0x0);
	DATA_TYPE s;
	long result;
	char t;
	s=m-imm-cpu.eflags.CF;
	result=m-imm-cpu.eflags.CF;
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
	REG(0x0)=s;
	print_asm("sbb" str(SUFFIX) " al,$0x%x",imm);
	return 1+DATA_BYTE;
}

#include "exec/template-end.h"
