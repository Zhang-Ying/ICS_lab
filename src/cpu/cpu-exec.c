#include "ui/ui.h"

#include "nemu.h"

#include <setjmp.h>

#define LOADER_START 0x100000
void breakpoint_preset();
void breakpoint_reset(swaddr_t n);
int exec(swaddr_t);
void load_prog();
void init_dram();
void init_cache_L1();
void init_cache_L2();
char assembly[40];
jmp_buf jbuf;	/* Make it easy to perform exception handling */

extern uint8_t loader [];
extern uint32_t loader_len;

extern int quiet;

void restart() {
	/* Perform some initialization to restart a program */
	load_prog();
	memcpy(hwa_to_va(LOADER_START), loader, loader_len);
    cpu.ebp=0;
	cpu.eip = LOADER_START;
    cpu.esp=0x80000000;
	cpu.eflags.E=0x2;
	cpu.eflags.CF=0;
	cpu.eflags.PF=0;
	cpu.eflags.AF=0;
	cpu.eflags.ZF=0;
	cpu.eflags.SF=0;
	cpu.eflags.TF=0;
	cpu.eflags.IF=0;
	cpu.eflags.DF=0;
	cpu.eflags.IO_PL=0;
	cpu.eflags.NT=0;
	cpu.eflags.RF=0;
	cpu.eflags.VM=0;
	init_dram();
	init_cache_L1();
	init_cache_L2();
}

static void print_bin_instr(swaddr_t eip, int len) {
	/*To show the relations between instructions and addresses*/
	int i;
	printf("%8x:   ", eip);
	for(i = 0; i < len; i ++) {
		printf("%02x ", swaddr_read(eip + i, 1));
	}
	printf("%*.s", 50 - (12 + 3 * len), "");
}

void cpu_exec(volatile uint32_t n) {
	/*The main loop to save and show the programming state*/
	volatile uint32_t n_temp = n;
	static int p=0;
	setjmp(jbuf);
	if(p%2==0)
		breakpoint_preset();
	else{
		p++;
	} 
	for(; n > 0; n --) {
		swaddr_t eip_temp = cpu.eip;
		int instr_len = exec(cpu.eip);
         
		cpu.eip += instr_len;
		if(n_temp != -1 || (enable_debug && !quiet)) {
			print_bin_instr(eip_temp, instr_len);
			puts(assembly);
		}
		if(nemu_state == INT){
			printf("\n\nUser interrupt\n");
			if(swaddr_read(cpu.eip-1,1)==204){
				cpu.eip--;
				breakpoint_reset(cpu.eip);
				p++;
			}
			return;
		    }
		else if(nemu_state == END) {
		   	return; 
		}
	} 
}
