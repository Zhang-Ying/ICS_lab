#include "exec/helper.h"

#define DATA_BYTE 2
#include "dec-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "dec-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(dec_r_v){
	return (suffix=='l'?dec_r_l(eip):dec_r_w(eip));
}
