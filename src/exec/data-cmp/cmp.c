#include "exec/helper.h"

#define DATA_BYTE 1
#include "cmp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "cmp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "cmp-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(cmp_rm2ie_v){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	if(m.reg==0x7)
	   	return (suffix == 'l' ? cmp_rm2ie_l(eip) : cmp_rm2ie_w(eip));
	else if(m.reg==0x5)
		return (suffix=='l'?sub_rm2ie_l(eip):sub_rm2ie_w(eip));
	else if(m.reg==0x4)
		return (suffix=='l'?and_rm2ie_l(eip):and_rm2ie_w(eip));
	else if(m.reg==0x0){
		printf("haha\n");
		return (suffix=='l'?add_rm2ie_l(eip):add_rm2ie_w(eip));
	}
	else if(m.reg==0x2)
		return (suffix=='l'?adc_rm2ie_l(eip):adc_rm2ie_w(eip));
	else if(m.reg==0x1)
		return (suffix=='l'?or_rm2ie_l(eip):or_rm2ie_w(eip));
	else if(m.reg==0x6)
		return (suffix=='l'?xor_rm2ie_l(eip):xor_rm2ie_w(eip));
	else if(m.reg==0x3)
		return (suffix=='l'?sbb_rm2ie_l(eip):sbb_rm2ie_w(eip));
	else
		return 0;
}
make_helper(cmp_rm2r_v){
	return (suffix=='l'?cmp_rm2r_l(eip):cmp_rm2r_w(eip));
}
make_helper(cmp_r2rm_v){
	return (suffix=='l'?cmp_r2rm_l(eip):cmp_r2rm_w(eip));
}
make_helper(cmp_al_v){
	return (suffix=='l'?cmp_al_l(eip):cmp_al_w(eip));
}
