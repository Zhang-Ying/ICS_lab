#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(jmp_r_,SUFFIX)){
	DATA_TYPE imm=instr_fetch(eip+1,DATA_BYTE);
	cpu.eip+=imm+1+DATA_BYTE;
	if(DATA_BYTE==2)
		cpu.eip=cpu.eip&0x0000FFFF;
	print_asm("jmp" str(SUFFIX) " %x",cpu.eip);
	return 0;
}
make_helper(concat(jmp_rm_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	if(m.mod==3)
		cpu.eip=REG(m.R_M);
	else{
		swaddr_t addr;
		read_ModR_M(eip+1,&addr);
		cpu.eip=addr;
	}
	print_asm("jmp" str(SUFFIX) " %x",cpu.eip);
	return 0;
}
make_helper(concat(call_rm_,SUFFIX)){
	ModR_M m;
	DATA_TYPE imm;
	m.val=instr_fetch(eip+1,1);
	if(m.mod==3)
		imm=REG(m.R_M);
	else{
		swaddr_t addr;
		read_ModR_M(eip+1+1,&addr);
		imm=swaddr_read(addr,DATA_BYTE);
	}
	if(DATA_BYTE==2){
		cpu.esp=cpu.esp+DATA_BYTE;
		REG(4)=cpu.eip|0x0000FFFF;
		cpu.eip=imm&0x0000FFFF;
	}
	else{
		cpu.esp=cpu.esp+DATA_BYTE;
		REG(4)=cpu.eip;
		cpu.eip=imm;
	}
	print_asm("call" str(SUFFIX) " %x",cpu.eip);
	return 0;
}
make_helper(concat(inc_rx_,SUFFIX)){
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
make_helper(concat(push_m_,SUFFIX)){
	int m=instr_fetch(eip+1,4);
	DATA_TYPE imm=MEM_R(m);
	REG(4)-=DATA_BYTE;
	MEM_W(REG(4),imm);
	print_asm("push" str(SUFFIX) " 0x%x",m);
	return 1+4;
}
make_helper(concat(dec_rm_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	char t;
	if(m.mod==3){
		DATA_TYPE s=REG(m.R_M);
		REG(m.R_M)=REG(m.R_M)-1;
		if(s<1){
			cpu.eflags.CF=1;
			cpu.eflags.SF=1;
		}
		else{
			cpu.eflags.CF=0;
			cpu.eflags.SF=0;
		}
		if(REG(m.R_M)==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(s<0&&REG(m.R_M)>0)
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		t=REG(m.R_M)&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		print_asm("dec" str(SUFFIX) " %%%s",REG_NAME(m.R_M));
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len;
		len=read_ModR_M(eip+1,&addr);
		DATA_TYPE s=MEM_R(addr);
		MEM_W(addr,MEM_R(addr)-1);
		if(s<1){
			cpu.eflags.CF=1;
			cpu.eflags.SF=1;
		}
		else{
			cpu.eflags.CF=0;
			cpu.eflags.SF=0;
		} 
		if(MEM_R(addr)==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(s<0&&MEM_R(addr)>0)
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		t=MEM_R(addr)&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		print_asm("dec" str(SUFFIX) " %s",ModR_M_asm);
		return 1+len;
	}
}

#include "exec/template-end.h"
