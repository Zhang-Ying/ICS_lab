#include "exec/helper.h"

#define DATA_BYTE 1
#include "jmp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jmp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jmp-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(jmp_r_v){
	return (suffix=='l'?jmp_r_l(eip):jmp_r_w(eip));
}
make_helper(jmp_rm_v){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	if(m.reg==0x4)
		return (suffix=='l'?jmp_rm_l(eip):jmp_rm_w(eip));
	else if(m.reg==0x2)
		return (suffix=='l'?call_rm_l(eip):call_rm_w(eip));
	else if(m.reg==0x0)
		return (suffix=='l'?inc_rx_l(eip):inc_rx_w(eip));
	else if(m.reg==0x6)
		return (suffix=='l'?push_m_l(eip):push_m_w(eip));
	else if(m.reg==0x1)
		return (suffix=='l'?dec_rm_l(eip):dec_rm_w(eip));
	else
		return 0;
}

