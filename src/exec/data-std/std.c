#include "exec/helper.h"

#define DATA_BYTE 1
#undef DATA_BYTE

#define DATA_BYTE 2
#undef DATA_BYTE

#define DATA_BYTE 4
#undef DATA_BYTE

make_helper(std){
	cpu.eflags.DF=1;
	print_asm("std");
	return 1;
}
