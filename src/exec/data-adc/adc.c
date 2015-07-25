#include "exec/helper.h"

#define DATA_BYTE 1
#include "adc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "adc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "adc-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(adc_rm2r_v){
	return (suffix=='l'?adc_rm2r_l(eip):adc_rm2r_w(eip));
}
make_helper(adc_r2rm_v){
	return (suffix=='l'?adc_r2rm_l(eip):adc_r2rm_w(eip));
}
make_helper(adc_ax2i_v){
	return (suffix=='l'?adc_ax2i_l(eip):adc_ax2i_w(eip));
}

