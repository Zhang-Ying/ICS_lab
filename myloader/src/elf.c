#include <elf.h>
#include "trap.h"

void loader(){
	Elf32_Ehdr *elf=(void *)0;
	Elf32_Phdr *ph=(Elf32_Phdr*)(elf+elf->e_phoff*2);
	int nr_hdr_entry=elf->e_phnum;
    int i=0;
	int count=0;
	char* vaddr;
	char* offset;
	for(i=0;i<nr_hdr_entry;i++){
	 	if(ph[i].p_type==PT_LOAD){
			vaddr=(char*)ph[i].p_vaddr;
			offset=(char*)ph[i].p_offset;
			for(count=0;count<ph[i].p_filesz;count++)
				vaddr[count]=offset[count];
			for(count=0;count<ph[i].p_memsz-ph[i].p_filesz;count++)
				(vaddr+ph[i].p_filesz)[count]=0;
		}
 	}

	((void(*)(void)) elf->e_entry) ();

	HIT_GOOD_TRAP;
}
