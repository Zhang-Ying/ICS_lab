#include "exec/helper.h"

#include "all-instr.h"

typedef int (*helper_fun)(swaddr_t);


/* TODO: Add more instructions!!! */

helper_fun opcode_table [256] = {
/* 0x00 */	add_rm2r_b,add_rm2r_v,add_r2rm_b,add_r2rm_v, 
/* 0x04 */	add_al_b,add_al_v, inv, inv, 
/* 0x08 */	or_rm2r_b,or_rm2r_v,or_r2rm_b,or_r2rm_v, 
/* 0x0c */	or_al_b,or_al_v, inv,jcc_v, 
/* 0x10 */	adc_rm2r_b,adc_rm2r_v,adc_r2rm_b,adc_r2rm_v, 
/* 0x14 */	adc_ax2i_b,adc_ax2i_v, inv, inv, 
/* 0x18 */	sbb_rm2r_b,sbb_rm2r_v,sbb_r2rm_b,sbb_r2rm_v, 
/* 0x1c */	sbb_al_b,sbb_al_v, inv, inv, 
/* 0x20 */	and_rm2r_b,and_rm2r_v,and_r2rm_b,and_r2rm_v, 
/* 0x24 */	and_al_b,and_al_v, inv, inv,
/* 0x28 */	sub_rm2r_b,sub_rm2r_v,sub_r2rm_b,sub_r2rm_v, 
/* 0x2c */	sub_al_b, sub_al_v, inv, inv, 
/* 0x30 */	xor_rm2r_b,xor_rm2r_v,xor_r2rm_b,xor_r2rm_v, 
/* 0x34 */	xor_al_b,xor_al_v, inv, inv,
/* 0x38 */	cmp_rm2r_b,cmp_rm2r_v,cmp_r2rm_b,cmp_r2rm_v, 
/* 0x3c */	cmp_al_b,cmp_al_v, inv, inv, 
/* 0x40 */	inc_r_v,inc_r_v,inc_r_v,inc_r_v, 
/* 0x44 */	inc_r_v,inc_r_v,inc_r_v,inc_r_v,
/* 0x48 */	dec_r_v,dec_r_v,dec_r_v,dec_r_v, 
/* 0x4c */	dec_r_v,dec_r_v,dec_r_v,dec_r_v, 
/* 0x50 */	push_r_v, push_r_v, push_r_v, push_r_v, 
/* 0x54 */	push_r_v, push_r_v, push_r_v, push_r_v,
/* 0x58 */	pop_r_v,pop_r_v,pop_r_v,pop_r_v, 
/* 0x5c */	pop_r_v,pop_r_v,pop_r_v,pop_r_v, 
/* 0x60 */	inv, inv, inv, inv,
/* 0x64 */	inv, inv, data_size, inv,
/* 0x68 */	push_i_v,imul_r2i_v,push_i_b,imul_r2rm2i_v, 
/* 0x6c */	inv, inv, inv, inv, 
/* 0x70 */	jcc_jo,jcc_jno,jcc_jb,jcc_jae,
/* 0x74 */	jcc_je,jcc_jne,jcc_jbe,jcc_ja,
/* 0x78 */	jcc_js,jcc_jns,jcc_jp,jcc_jnp,
/* 0x7c */	jcc_jl,jcc_jge,jcc_jle,jcc_jg, 
/* 0x80 */	sub_rm2i_v,sub_rm2i_v, nemu_trap, cmp_rm2ie_v, 
/* 0x84 */	test_rm2r_b, test_rm2r_v,xchg_rm2r_b,xchg_rm2r_v, 
/* 0x88 */	mov_r2rm_b, mov_r2rm_v, mov_rm2r_b, mov_rm2r_v,
/* 0x8c */	inv,lea_r2m_v, inv,pop_m_v, 
/* 0x90 */	xchg_ax2r_v,xchg_ax2r_v,xchg_ax2r_v,xchg_ax2r_v,
/* 0x94 */	xchg_ax2r_v,xchg_ax2r_v,xchg_ax2r_v,xchg_ax2r_v,
/* 0x98 */	inv, inv, inv, inv, 
/* 0x9c */	inv, inv, inv, inv, 
/* 0xa0 */	mov_moffs2a_b, mov_moffs2a_v, mov_a2moffs_b, mov_a2moffs_v,
/* 0xa4 */	movs_m_b,movs_m_v, inv, inv,
/* 0xa8 */	test_r2i_b, test_r2i_v, inv, inv,
/* 0xac */	inv, inv, inv, inv,
/* 0xb0 */	mov_i2r_b, mov_i2r_b, mov_i2r_b, mov_i2r_b,
/* 0xb4 */	mov_i2r_b, mov_i2r_b, mov_i2r_b, mov_i2r_b,
/* 0xb8 */	mov_i2r_v, mov_i2r_v, mov_i2r_v, mov_i2r_v, 
/* 0xbc */	mov_i2r_v, mov_i2r_v, mov_i2r_v, mov_i2r_v, 
/* 0xc0 */	sal_rm2i_v,sal_rm2i_v,ret_i,ret,
/* 0xc4 */	inv, inv, mov_i2rm_b, mov_i2rm_v,
/* 0xc8 */	inv,leave_v, inv, inv,
/* 0xcc */	int3, inv, inv, inv,
/* 0xd0 */	sal_rm21_v,sal_rm21_v,sal_rm2cl_v,sal_rm2cl_v,
/* 0xd4 */	inv, inv, inv, inv,
/* 0xd8 */	inv, inv, inv, inv,
/* 0xdc */	inv, inv, inv, inv,
/* 0xe0 */	inv, inv, inv, inv,
/* 0xe4 */	inv, inv, inv,jcc_jcxz,
/* 0xe8 */	call_r_v,jmp_r_v, inv,jmp_r_b,
/* 0xec */	inv, inv, inv, inv,
/* 0xf0 */	inv, inv, inv,rep_movs_v,
/* 0xf4 */	inv, inv, test_rm2i_v, test_rm2i_v,
/* 0xf8 */	inv, inv, inv, inv,
/* 0xfc */	cld,std,inc_rm_b,jmp_rm_v
};

make_helper(exec) {
	return opcode_table[ instr_fetch(eip, 1) ](eip);
}
