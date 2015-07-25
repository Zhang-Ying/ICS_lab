#include "exec/helper.h"

#define DATA_BYTE 1
#undef DATA_BYTE

#define DATA_BYTE 2
#undef DATA_BYTE

#define DATA_BYTE 4
#undef DATA_BYTE

make_helper(cld){
	cpu.eflags.DF=0;
	print_asm("cld");
	return 1;
}
