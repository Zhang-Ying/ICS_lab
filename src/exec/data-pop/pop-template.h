#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(pop_r_,SUFFIX)){
	int regcode;
	char m;
	m=instr_fetch(eip,1);
	regcode=m&0x7;
	REG(regcode)=MEM_R(REG(4));
	cpu.esp+=DATA_BYTE;
	print_asm("pop" str(SUFFIX) " %%%s",REG_NAME(regcode));
	return 1;
}
make_helper(concat(pop_m_,SUFFIX)){
	DATA_TYPE imm=instr_fetch(eip+1,DATA_BYTE);
	REG(4)=imm;
	cpu.esp+=DATA_BYTE;
	print_asm("pop" str(SUFFIX) " 0x%x",imm);
	return 1+DATA_BYTE;
}

#include "exec/template-end.h"
	

