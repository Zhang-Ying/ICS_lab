#include "exec/helper.h"

#define DATA_BYTE 1
#include "xor-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "xor-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "xor-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(xor_rm2r_v){
	return (suffix=='l'?xor_rm2r_l(eip):xor_rm2r_w(eip));
}
make_helper(xor_r2rm_v){
	return (suffix=='l'?xor_r2rm_l(eip):xor_r2rm_w(eip));
}
make_helper(xor_al_v){
	return (suffix=='l'?xor_al_l(eip):xor_al_w(eip));
}

