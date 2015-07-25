#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(imul_r2rm2i_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	cpu.eflags.OF=cpu.eflags.CF=0;
 	if(m.mod==3){
		char imm=instr_fetch(eip+1+1,1);
 		if(DATA_BYTE==2){
			imm=(short)imm;
			if(imm>>7!=0)
				imm=imm|0xff00;
		}
 		else{
			imm=(int)imm;
			if(imm>>7!=0)
				imm=imm|0xffffff00;
		}
		REG(m.reg)=REG(m.R_M)*imm;
		printf("%%%s=%d,%%%s=%d\n",REG_NAME(m.R_M),REG(m.R_M),REG_NAME(m.reg),REG(m.reg));
		print_asm("imul" str(SUFFIX) " 0x%x,%%%s,%%%s",imm,REG_NAME(m.R_M),REG_NAME(m.reg));
		return 1+1+1;
	}
 	else{ 
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE s=swaddr_read(addr,DATA_BYTE);
		char imm=instr_fetch(eip+1+len,1);
 		if(DATA_BYTE==2){
			imm=(short)imm;
			if(imm<0)
				imm=imm|0xff00;
		}
		else{
			imm=(int)imm;
			if(imm<0)
				imm=imm|0xffffff00;
		} 
		REG(m.reg)=s*imm;
		print_asm("imul" str(SUFFIX) " 0x%x,%s,%%%s",imm,ModR_M_asm,REG_NAME(m.reg));
		return 1+len+1;
	}
}
make_helper(concat(imul_r2i_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	if(m.mod==3){
		DATA_TYPE imm=instr_fetch(eip+1+1,DATA_BYTE);
		REG(m.reg)=REG(m.R_M)*imm;
		print_asm("imul" str(SUFFIX) " 0x%x,%%%s,%%%s",imm,REG_NAME(m.R_M),REG_NAME(m.reg));
		return 1+1+DATA_BYTE;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE s=swaddr_read(addr,DATA_BYTE);
		DATA_TYPE imm=instr_fetch(eip+1+len,DATA_BYTE);
		REG(m.reg)=s*imm;
		print_asm("imul" str(SUFFIX) " 0x%x,%s,%%%s",imm,ModR_M_asm,REG_NAME(m.reg));
		return 1+len+DATA_BYTE;
	}
}

#include "exec/template-end.h"
			

