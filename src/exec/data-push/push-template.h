#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(push_r_,SUFFIX)){
	int reg_code = instr_fetch(eip,1) & 0x7;
	cpu.esp=cpu.esp-DATA_BYTE;
	MEM_W(REG(4),REG(reg_code));
	print_asm("push" str(SUFFIX) " %%%s",REG_NAME(reg_code));
	return 1;
}
make_helper(concat(push_i_,SUFFIX)){
	DATA_TYPE imm;
	imm=instr_fetch(eip+1,DATA_BYTE);
	cpu.esp=cpu.esp-DATA_BYTE;
	MEM_W(REG(4),imm);
	print_asm("push" str(SUFFIX) " 0x%x",imm);
	return 1+DATA_BYTE;
}

#include "exec/template-end.h"
