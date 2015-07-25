#include "exec/helper.h"

#define DATA_BYTE 1
#include "sub-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "sub-template.h"
#undef  DATA_BYTE

#define DATA_BYTE 4
#include "sub-template.h"
#undef DATA_BYTE


extern char suffix;

make_helper(sub_rm2r_v){
	return (suffix=='l'?sub_rm2r_l(eip):sub_rm2r_w(eip));
}

make_helper(sub_r2rm_v){
	return (suffix=='l'?sub_r2rm_l(eip):sub_r2rm_w(eip));
}

make_helper(sub_rm2i_v){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	int n=instr_fetch(eip,1);
	if(m.reg==0x5){
		if(n==0x80)
			return sub_rm2i_b(eip);
		else
			return (suffix=='l'?sub_rm2i_l(eip):sub_rm2i_w(eip));
	}
	else if(m.reg==0x4){
		if(n==0x80)
			return and_rm2i_b(eip);
		else
			return (suffix=='l'?and_rm2i_l(eip):and_rm2i_w(eip));
	}
	else if(m.reg==0x7){
		if(n==0x80)
			return cmp_rm2i_b(eip);
		else
			return (suffix=='l'?cmp_rm2i_l(eip):cmp_rm2i_w(eip));
	}
	else if(m.reg==0x2){
		if(n==0x80)
			return adc_rm2i_b(eip);
		else
			return (suffix=='l'?adc_rm2i_l(eip):adc_rm2i_w(eip));
	}
	else if(m.reg==0x1){
		if(n==0x80)
			return or_rm2i_b(eip);
		else
			return (suffix=='l'?or_rm2i_l(eip):or_rm2i_w(eip));
	}
	else if(m.reg==0x6){
		if(n==0x80)
			return xor_rm2i_b(eip);
		else
			return (suffix=='l'?xor_rm2i_l(eip):xor_rm2i_w(eip));
	}
	else if(m.reg==0x0){
		if(n==0x80)
			return add_rm2i_b(eip);
		else
			return (suffix=='l'?add_rm2i_l(eip):add_rm2i_w(eip));
	}
	else if(m.reg==0x3){
		if(n==0x80)
			return sbb_rm2i_b(eip);
		else
			return (suffix=='l'?sbb_rm2i_l(eip):sbb_rm2i_w(eip));
	}
	else
		return 0;
}

make_helper(sub_al_v){
	return (suffix=='l'?sub_al_l(eip):sub_al_w(eip));
}
