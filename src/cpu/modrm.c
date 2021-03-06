#include "cpu/modrm.h"

#include "exec/helper.h"

#include "nemu.h"

int current_sreg;
char ModR_M_asm[MODRM_ASM_BUF_SIZE];
#define print_ModR_M_asm(...) \
	assert(snprintf(ModR_M_asm, MODRM_ASM_BUF_SIZE, __VA_ARGS__) < MODRM_ASM_BUF_SIZE )

/* For more details about instruction format, please refer to i386 manual. */
 int read_ModR_M(swaddr_t eip, swaddr_t *addr) {
	ModR_M m;
	m.val = instr_fetch(eip, 1);
	int32_t disp;
	int instr_len, disp_offset, disp_size;
	int base_reg = -1, index_reg = -1, scale = 0;

	/* When m.mod == 3, the instruct ion is not going to access memory.
	 * This situation should be handle before calling read_ModR_M(). 
	 * Therefore, m.mod should not be 3 here.
 	 */
	assert(m.mod != 3);
	disp_size = 4;
 	if(m.R_M == R_ESP) { 
		SIB s;
		s.val = instr_fetch(eip + 1, 1);
		base_reg = s.base;
		disp_offset = 2;
		scale = s.ss;

		if(s.index != R_ESP) { index_reg = s.index; }
 	}
 	else {
		/* no SIB */
		base_reg = m.R_M;
		disp_offset = 1;
	}

	if(m.mod == 0) {
		if(base_reg == R_EBP) { base_reg = -1; }
		else { disp_size = 0; }
 	}
	else if(m.mod == 1) { disp_size = 1; }


	char disp_buf[16];
	char base_buf[8];
	char index_buf[8];

	instr_len = disp_offset;
	*addr = 0;
	if(disp_size != 0) {
		/* has disp */
		disp = instr_fetch(eip + disp_offset, disp_size);
		if(disp_size == 1) { disp = (int8_t)disp; }
		sprintf(disp_buf, "%s%#x", (disp < 0 ? "-" : ""), (disp < 0 ? -disp : disp));
		instr_len += disp_size;
		*addr += disp;
 	}
	else { disp_buf[0] = '\0'; }

 	if(base_reg == -1) { base_buf[0] = '\0'; }
 	else { 
		sprintf(base_buf, "%%%s", regsl[base_reg]); 
		*addr += reg_l(base_reg);
 	}

	if(index_reg == -1) { index_buf[0] = '\0'; }
	else { 
		sprintf(index_buf, ",%%%s,%d", regsl[index_reg], 1 << scale); 
		*addr += reg_l(index_reg) << scale;
  	}

	if(base_reg == -1 && index_reg == -1) {
		print_ModR_M_asm("%s", disp_buf);
 	}
	else {
		print_ModR_M_asm("%s(%s%s)", disp_buf, base_buf, index_buf);
 	}
    
	if(base_reg!=-1){
		if(base_reg==4)
			current_sreg=2;
		else
			current_sreg=3;
	}
	else
		current_sreg=-1;
	return instr_len;
}

