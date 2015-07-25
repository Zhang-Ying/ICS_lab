#include "exec/helper.h"

#define DATA_BYTE 1
#include "ret-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "ret-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "ret-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(ret_i){
	cpu.eip=swaddr_read(cpu.esp,4);
	cpu.esp+=4;
	short imm=instr_fetch(eip+1,2);
	cpu.esp+=imm;
	print_asm("ret" " %x",imm);
	return 0;
}
make_helper(ret){
	cpu.eip=swaddr_read(cpu.esp,4);
	cpu.esp+=4;
	print_asm("ret");
	return 0;
}
