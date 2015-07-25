#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(movs_m_,SUFFIX)){
	DATA_TYPE imm;
	imm=MEM_R(REG(6));
	MEM_W(REG(7),imm);
	print_asm("movs" str(SUFFIX));
	return 1;
}

#include "exec/template-end.h"
