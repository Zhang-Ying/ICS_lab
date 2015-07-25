#include "exec/helper.h"

#define DATA_BYTE 1
#include "sal-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "sal-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "sal-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(sal_rm21_v){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	int n;
	n=instr_fetch(eip,1);
	if(m.reg==0x4){
		if(n==0xd0)
			return sal_rm21_b(eip);
		else
			return suffix=='l'?sal_rm21_l(eip):sal_rm21_w(eip);
	}
	else if(m.reg==0x5){
		if(n==0xd0)
			return shr_rm21_b(eip);
		else
			return suffix=='l'?shr_rm21_l(eip):shr_rm21_w(eip);
	}
	else if(m.reg==0x7){
		if(n==0xd0)
			return sar_rm21_b(eip);
		else
			return suffix=='l'?sar_rm21_l(eip):sar_rm21_w(eip);
	}
	else 
		return 0;
}
make_helper(sal_rm2cl_v){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	int n;
	n=instr_fetch(eip,1);
	if(m.reg==0x4){
		if(n==0xd2)
			return sal_rm2cl_b(eip);
		else
			return suffix=='l'?sal_rm2cl_l(eip):sal_rm2cl_w(eip);
	}
	else if(m.reg==0x5){
		if(n==0xd2)
			return shr_rm2cl_b(eip);
		else
			return suffix=='l'?shr_rm2cl_l(eip):shr_rm2cl_w(eip);
	}
	else if(m.reg==0x7){
		if(n==0xd2)
			return sar_rm2cl_b(eip);
		else
			return suffix=='l'?sar_rm2cl_l(eip):sar_rm2cl_w(eip);
	}
	else 
		return 0;
}
make_helper(sal_rm2i_v){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	int n;
	n=instr_fetch(eip,1);
	if(m.reg==0x4){
		if(n==0xc0)
			return sal_rm2i_b(eip);
		else
			return suffix=='l'?sal_rm2i_l(eip):sal_rm2i_w(eip);
	}
	else if(m.reg==0x5){
		if(n==0xc0)
			return shr_rm2i_b(eip);
		else
			return suffix=='l'?shr_rm2i_l(eip):shr_rm2i_w(eip);
	}
	else if(m.reg==0x7){
		if(n==0xc0)
			return sar_rm2i_b(eip);
		else
			return suffix=='l'?sar_rm2i_l(eip):sar_rm2i_w(eip);
	}
	else 
		return 0;
}
