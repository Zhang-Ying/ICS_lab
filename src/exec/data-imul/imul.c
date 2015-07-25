#include "exec/helper.h"

#define DATA_BYTE 1
#include "imul-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "imul-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "imul-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(imul_r2rm2i_v){
	return (suffix=='l'?imul_r2rm2i_l(eip):imul_r2rm2i_w(eip));
}
make_helper(imul_r2i_v){
	return (suffix=='l'?imul_r2i_l(eip):imul_r2i_w(eip));
}

