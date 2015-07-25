#include "common.h"
#include "memory.h"

#include <elf.h>


#ifdef HAS_DEVICE
#define ELF_OFFSET_IN_DISK 0
#endif

#define STACK_SIZE (1 << 20)

void ide_read(uint8_t *, uint32_t, uint32_t);
void disk_do_read(void *, uint32_t);
void disk_do_write(void *, uint32_t);
void create_video_mapping();
uint32_t get_ucr3();

uint32_t loader() {
	Elf32_Ehdr *elf;

#ifdef HAS_DEVICE
	uint8_t buf[4096];
	ide_read(buf, ELF_OFFSET_IN_DISK, 4096);
	elf = (void*)buf;
#else
	/* The ELF file is located at memory address 0 */
	elf = (void *)0x0;
#endif

	/* Load each program segment */
/*	Elf32_Phdr *ph=(Elf32_Phdr*)(elf+elf->e_phoff*2);
	int nr_hdr_entry=elf->e_phnum;
	nemu_assert(nr_hdr_entry==2);
	nemu_assert(elf->e_phoff==52);
	int i=0;
	int count=0;
	char* vaddr;
	char* offset;
	for(i=0;i<nr_hdr_entry;i++){
 		if(ph[i].p_type==PT_LOAD){
			nemu_assert(i==0);
			nemu_assert(ph[i].p_vaddr!=0x8048000);
			nemu_assert(ph[i].p_offset==0x0);
			nemu_assert(ph[i].p_filesz==0xcc);
			nemu_assert(ph[i].p_memsz==0xcc);
			vaddr=(char*)ph[i].p_vaddr;
			offset=(char*)ph[i].p_offset;
			nemu_assert(offset[20]==2);
			for(count=0;count<ph[i].p_filesz;count++)
				*(vaddr+count)=offset[count];
			for(count=0;count<ph[i].p_memsz-ph[i].p_filesz;count++)
				*(vaddr+ph[i].p_filesz+count)=0;
  		}*/
			/* Record the prgram break for future use. */
/*	extern uint32_t brk;
	uint32_t new_brk = ph[i].p_vaddr + ph[i].p_memsz - 1;
	if(brk < new_brk) { brk = new_brk; }
   	}
*/
   	char *vaddr1=(char*)0x8048000;
	int filesz1=0x194;
	int memsz1=0x194;
	char* offset1=0;
	char* vaddr2=(char*)0x80491a0;
	int filesz2=0x0;
	int memsz2=0x48;
	char* offset2=(char*)0x1a0;
	int count=0;
	for(count=0;count<filesz1;count++)
		*(vaddr1+count)=offset1[count];
	for(count=0;count<memsz1-filesz1;count++)
		*(vaddr1+filesz1+count)=0;
	for(count=0;count<filesz2;count++)
		*(vaddr2+count)=offset2[count];
	for(count=0;count<memsz2-filesz2;count++)
		*(vaddr2+filesz2+count)=0;
	volatile uint32_t entry = elf->e_entry;

#ifdef IA32_PAGE
	mm_malloc(KOFFSET - STACK_SIZE, STACK_SIZE);

#ifdef HAS_DEVICE
	create_video_mapping();
#endif

	write_cr3(get_ucr3());
#endif

	return entry;
}
