#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(adc_rm2r_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	DATA_TYPE s;
	long result;
	char t;
	if(m.mod==3){
		s=REG(m.reg)+REG(m.R_M)+cpu.eflags.CF;
		result=REG(m.reg)+REG(m.R_M)+cpu.eflags.CF;
		REG(m.R_M)=s;
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
		print_asm("adc" str(SUFFIX) " %%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));
		return 1+1;
	} 
	else{ 
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		s=swaddr_read(addr,4)+REG(m.reg)+cpu.eflags.CF;
		result=swaddr_read(addr,4)+REG(m.reg)+cpu.eflags.CF;
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
		print_asm("adc" str(SUFFIX) " %%%s,%s",REG_NAME(m.reg),ModR_M_asm);
		return 1+len;
	}
}
make_helper(concat(adc_r2rm_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	DATA_TYPE s;
	long result;
	char t;
	if(m.mod==3){
		s=REG(m.reg)+REG(m.R_M)+cpu.eflags.CF;
		result=REG(m.reg)+REG(m.R_M)+cpu.eflags.CF;
		REG(m.reg)=s;
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
		print_asm("adc" str(SUFFIX) " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
		return 1+1;
	} 
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		s=REG(m.reg)+ swaddr_read(addr,4)+cpu.eflags.CF;
		result=REG(m.reg)+swaddr_read(addr,4)+cpu.eflags.CF;
		REG(m.reg)=s;
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
		print_asm("adc" str(SUFFIX) " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));
		return 1+len;
	}
}
make_helper(concat(adc_ax2i_,SUFFIX)){
	DATA_TYPE imm=instr_fetch(eip+1,DATA_BYTE);
	DATA_TYPE imm1;
	DATA_TYPE s;
	long result;
	char t;
	if(DATA_BYTE==1)
		imm1=REG(0)&0x000000FF;
	else if(DATA_BYTE==2)
		imm1=REG(0)&0x0000FFFF;
	else
		imm1=REG(0);
	s=imm1+imm+cpu.eflags.CF;
	result=imm1+imm+cpu.eflags.CF;
	REG(0)=s;
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
	print_asm("adc" str(SUFFIX) " %x,%%%s",imm,REG_NAME(0));
	return DATA_BYTE+1;
}

#include "exec/template-end.h"
