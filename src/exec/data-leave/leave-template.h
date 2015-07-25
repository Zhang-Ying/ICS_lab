#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(leave_,SUFFIX)){
	REG(4)=REG(5);
	REG(5)=MEM_R(REG(4));
	cpu.esp+=DATA_BYTE;
	print_asm("leave");
	return 1;
}
#include "exec/template-end.h"
