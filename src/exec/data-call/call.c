#include "exec/helper.h"

#define DATA_BYTE 1
#include "call-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "call-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "call-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(call_r_v){
	return (suffix=='l'?call_r_l(eip):call_r_w(eip));
}
