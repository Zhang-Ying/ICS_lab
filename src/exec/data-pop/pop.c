#include "exec/helper.h"

#define DATA_BYTE 1
#include "pop-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "pop-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "pop-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(pop_r_v){
	return (suffix=='l'?pop_r_l(eip):pop_r_w(eip));
}
make_helper(pop_m_v){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	if(m.reg==0x0)
		return (suffix=='l'?pop_m_l(eip):pop_m_w(eip));
	else
		return 0;
}
