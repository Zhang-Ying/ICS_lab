#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(call_r_,SUFFIX)){
	DATA_TYPE imm;
	imm=instr_fetch(eip+1,DATA_BYTE);
	cpu.esp-=DATA_BYTE;
	if(DATA_BYTE==2){
		MEM_W(cpu.esp,(cpu.eip+DATA_BYTE+1)|0x0000ffff);
		cpu.eip=(cpu.eip+imm)&0x0000FFFF;
	}
	else{
		MEM_W(cpu.esp,(cpu.eip+DATA_BYTE+1));
		cpu.eip+=imm;
	}
	print_asm("call" str(SUFFIX) " %x",cpu.eip+1+DATA_BYTE);
	return 1+DATA_BYTE;
}
#include "exec/template-end.h"



