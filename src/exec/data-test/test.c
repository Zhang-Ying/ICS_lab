#include "exec/helper.h"

#define DATA_BYTE 1
#include "test-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "test-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "test-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(test_r2i_v){
	return (suffix == 'l' ? test_r2i_l(eip) : test_r2i_w(eip));
}
make_helper(test_rm2i_v){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	int n;
	n=instr_fetch(eip,1);
	if(m.reg==0x0){
		if(n==0xf6)
			return test_rm2i_b(eip);
		else
			return (suffix == 'l' ? test_rm2i_l(eip) : test_rm2i_w(eip));
	}
	else if(m.reg==0x7){
		if(n==0xf6)
			return idiv_ax2rm_b(eip);
		else
			return (suffix=='l'?idiv_ax2rm_l(eip):idiv_ax2rm_w(eip));
	}
	else if(m.reg==0x5){
		if(n==0xf6)
			return imul_rm_b(eip);
		else
			return (suffix=='l'?imul_rm_l(eip):imul_rm_w(eip));
	}
	else if(m.reg==0x2){
		if(n==0xf6)
			return not_rm_b(eip);
		else
			return (suffix=='l'?not_rm_l(eip):not_rm_w(eip));
	}
	else if(m.reg==0x4){
		if(n==0xf6)
			return mul_ax2rm_b(eip);
		else
			return (suffix=='l'?mul_ax2rm_l(eip):mul_ax2rm_w(eip));
	}
	else if(m.reg==0x3){
		if(n==0xf6)
			return neg_rm_b(eip);
		else
			return (suffix=='l'?neg_rm_l(eip):neg_rm_w(eip));
	}
	else if(m.reg==0x6){
		if(n==0xf6)
			return div_ax2rm_b(eip);
		else
			return (suffix=='l'?div_ax2rm_l(eip):div_ax2rm_w(eip));
	}
	else
		return 0;
}
make_helper(test_rm2r_v){
	return (suffix == 'l' ? test_rm2r_l(eip) : test_rm2r_w(eip));
}
