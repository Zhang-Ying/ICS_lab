#ifndef __CPU_REG_H__
#define __CPU_REG_H__

#include "common.h"

/* TODO: Re-organize the 'CPU_state' structure to match
 * the GPR encoding scheme in i386 instruction format.
 * For example, if we access reg_w(R_BX) we will get the 'bx' register;
 * if we access reg_b(R_CH), we will get the 'ch' register.
 * Hint: Use 'union'.
 * For more details about the GPR encoding scheme, see i386 manual.
 */
typedef struct {
	unsigned CF:1;
	unsigned A:1;
	unsigned PF:1;
	unsigned B:1;
	unsigned AF:1;
	unsigned C:1;
	unsigned ZF:1;
	unsigned SF:1;
	unsigned TF:1;
	unsigned IF:1;
	unsigned DF:1;
	unsigned OF:1;
	unsigned IO_PL:2;
	unsigned NT:1;
	unsigned D:1;
	unsigned RF:1;
	unsigned VM:1;
	unsigned E:14;
}bs;
typedef struct{
	unsigned PE:1;
	unsigned MP:1;
	unsigned EM:1;
	unsigned TS:1;
	unsigned ET:1;
    unsigned :26;
  	unsigned PG:1;
}cr;	
typedef struct{
	unsigned limit:16;
	unsigned base:32;
}gdtr;
typedef union {
	union {
		uint32_t _32;
		uint16_t _16;
		uint8_t _8[2];
	} gpr[8]; 

	/* Do NOT  change the order of the GPRs' definitions. 
	 * They match the register encoding scheme used in i386 instruction format.
	 * See i386 manual for more details.
	 */
struct 
{
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
	uint32_t esp;
	uint32_t ebp;
	uint32_t esi;
	uint32_t edi;
	uint16_t CS;
	uint16_t DS;
	uint16_t ES;
	uint16_t SS;
    bs    eflags;
	cr CR0;
	gdtr GDTR;
	swaddr_t eip;
};
}CPU_state;

extern CPU_state cpu;

enum { R_EAX, R_ECX, R_EDX, R_EBX, R_ESP, R_EBP, R_ESI, R_EDI,R_EFLAGS };
enum { R_AX, R_CX, R_DX, R_BX, R_SP, R_BP, R_SI, R_DI ,R_FLAGS};
enum { R_AL, R_CL, R_DL, R_BL, R_AH, R_CH, R_DH, R_BH };

#define reg_l(index) (cpu.gpr[index]._32)
#define reg_w(index) (cpu.gpr[index]._16)
#define reg_b(index) (cpu.gpr[index & 0x3]._8[index >> 2])

extern const char* regsl[];
extern const char* regsw[];
extern const char* regsb[];

#endif
