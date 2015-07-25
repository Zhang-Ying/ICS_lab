#include "exec/helper.h"

#define DATA_BYTE 1
#include "rep-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "rep-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "rep-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(rep_movs_v){
	int imm;
 	imm=instr_fetch(eip+1,1);
	if(imm==0xa4)
		return rep_movs_b(eip);
	else if(imm==0xa5)
		return suffix=='l'?rep_movs_l(eip):rep_movs_w(eip);
	else
		return 0;
}
