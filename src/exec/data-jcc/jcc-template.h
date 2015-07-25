#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(jcc_jl_,SUFFIX)){
	DATA_TYPE addr;
	addr=instr_fetch(eip+1+1,DATA_BYTE);
	print_asm("jl %x <main+0x%x>",eip+1+DATA_BYTE+addr+1,(eip+1+DATA_BYTE+addr+1)-0x100000);
	if(cpu.eflags.SF!=cpu.eflags.OF&&cpu.eflags.ZF==0)
		return 1+1+DATA_BYTE+addr;
	else
		return 1+1+DATA_BYTE;
}
make_helper(concat(jcc_jbe_,SUFFIX)){
	DATA_TYPE addr;
	addr=instr_fetch(eip+1+1,DATA_BYTE);
	print_asm("jbe %x <main+0x%x>",eip+1+DATA_BYTE+addr+1,(eip+1+DATA_BYTE+addr+1)-0x100000);
	if(cpu.eflags.CF==1||cpu.eflags.ZF==1)
		return 1+1+DATA_BYTE+addr;
	else
		return 1+DATA_BYTE+1;
}
make_helper(concat(jcc_ja_,SUFFIX)){
	DATA_TYPE addr;
	addr=instr_fetch(eip+1+1,DATA_BYTE);
	print_asm("ja %x <main+0x%x>",eip+1+DATA_BYTE+addr+1,(eip+1+DATA_BYTE+addr+1)-0x100000);
	if(cpu.eflags.CF==0&&cpu.eflags.ZF==0)
		return 1+1+DATA_BYTE+addr;
	else
		return 1+DATA_BYTE+1;
}
 make_helper(concat(jcc_jae_,SUFFIX)){
	 DATA_TYPE addr;
	 addr=instr_fetch(eip+1+1,DATA_BYTE);
	 print_asm("jae %x <main+0x%x>",eip+1+DATA_BYTE+addr+1,(eip+1+DATA_BYTE+addr+1)-0x100000);
	 if(cpu.eflags.CF==0||cpu.eflags.ZF==0)
		 return 1+1+DATA_BYTE+addr;
	 else
		 return 1+DATA_BYTE+1;
 }
 make_helper(concat(jcc_jb_,SUFFIX)){
	 DATA_TYPE addr;
	 addr=instr_fetch(eip+1+1,DATA_BYTE);
	 print_asm("jb %x <main+0x%x>",eip+1+DATA_BYTE+addr+1,(eip+1+DATA_BYTE+addr+1)-0x100000);
	 if(cpu.eflags.CF==1&&cpu.eflags.ZF==0)
		 return 1+1+DATA_BYTE+addr;
	 else
		 return 1+DATA_BYTE+1;
 }
 make_helper(concat(jcc_je_,SUFFIX)){
	 DATA_TYPE addr;
	 addr=instr_fetch(eip+1+1,DATA_BYTE);
	 print_asm("je %x <main+0x%x>",eip+1+DATA_BYTE+addr+1,(eip+1+DATA_BYTE+addr+1)-0x100000);
	 if(cpu.eflags.ZF==1)
		 return 1+1+DATA_BYTE+addr;
	 else
		 return 1+DATA_BYTE+1;
 }
 make_helper(concat(jcc_jg_,SUFFIX)){
	 DATA_TYPE addr;
	 addr=instr_fetch(eip+1+1,DATA_BYTE);
	 print_asm("jg %x <main+0x%x>",eip+1+DATA_BYTE+addr+1,(eip+1+DATA_BYTE+addr+1)-0x100000);
	 if(cpu.eflags.SF==cpu.eflags.OF&&cpu.eflags.ZF==0)
		 return 1+1+DATA_BYTE+addr;
	 else
		 return 1+DATA_BYTE+1;
 }
 make_helper(concat(jcc_jge_,SUFFIX)){
	 DATA_TYPE addr;
	 addr=instr_fetch(eip+1+1,DATA_BYTE);
	 print_asm("jge %x <main+0x%x>",eip+1+DATA_BYTE+addr+1,(eip+1+DATA_BYTE+addr+1)-0x100000);
	 if(cpu.eflags.SF==cpu.eflags.OF||cpu.eflags.ZF==1)
		 return 1+1+DATA_BYTE+addr;
	 else
		 return 1+DATA_BYTE+1;
 }
 make_helper(concat(jcc_jno_,SUFFIX)){
	 DATA_TYPE addr;
	 addr=instr_fetch(eip+1+1,DATA_BYTE);
	 print_asm("jno %x <main+0x%x>",eip+1+DATA_BYTE+addr+1,(eip+1+DATA_BYTE+addr+1)-0x100000);
	 if(cpu.eflags.OF==0)
		 return 1+1+DATA_BYTE+addr;
	 else
		 return 1+DATA_BYTE+1;
 }
 make_helper(concat(jcc_jle_,SUFFIX)){
	 DATA_TYPE addr;
	 addr=instr_fetch(eip+1+1,DATA_BYTE);
	 print_asm("jle %x <main+0x%x>",eip+1+DATA_BYTE+addr+1,(eip+1+DATA_BYTE+addr+1)-0x100000);
	 if(cpu.eflags.SF!=cpu.eflags.OF||cpu.eflags.ZF==1)
		 return 1+1+DATA_BYTE+addr;
	 else
		 return 1+DATA_BYTE+1;
 }
 make_helper(concat(jcc_jne_,SUFFIX)){
	 DATA_TYPE addr;
	 addr=instr_fetch(eip+1+1,DATA_BYTE);
	 print_asm("jne %x <main+0x%x>",eip+1+DATA_BYTE+addr+1,(eip+1+DATA_BYTE+addr+1)-0x100000);
	 if(cpu.eflags.ZF==0)
		 return 1+1+DATA_BYTE+addr;
	 else
		 return 1+DATA_BYTE+1;
 }
 make_helper(concat(jcc_jnp_,SUFFIX)){
	 DATA_TYPE addr;
	 addr=instr_fetch(eip+1+1,DATA_BYTE);
	 print_asm("jnp %x <main+0x%x>",eip+1+DATA_BYTE+addr+1,(eip+1+DATA_BYTE+addr+1)-0x100000);
	 if(cpu.eflags.PF==0)
		 return 1+1+DATA_BYTE+addr;
	 else
		 return 1+DATA_BYTE+1;
 }
 make_helper(concat(jcc_jns_,SUFFIX)){
 	 DATA_TYPE addr;
	 addr=instr_fetch(eip+1+1,DATA_BYTE);
	 print_asm("jns %x <main+0x%x>",eip+1+DATA_BYTE+addr+1,(eip+1+DATA_BYTE+addr+1)-0x100000);
	 if(cpu.eflags.SF==0)
		 return 1+1+DATA_BYTE+addr;
	 else
		 return 1+DATA_BYTE+1;
 }
 make_helper(concat(jcc_jo_,SUFFIX)){
	 DATA_TYPE addr;
	 addr=instr_fetch(eip+1+1,DATA_BYTE);
	 print_asm("jo %x <main+0x%x>",eip+1+DATA_BYTE+addr+1,(eip+1+DATA_BYTE+addr+1)-0x100000);
	 if(cpu.eflags.OF==1)
		 return 1+1+DATA_BYTE+addr;
	 else
		 return 1+DATA_BYTE+1;
 }
 make_helper(concat(jcc_jp_,SUFFIX)){
	 DATA_TYPE addr;
	 addr=instr_fetch(eip+1+1,DATA_BYTE);
	 print_asm("jp %x <main+0x%x>",eip+1+DATA_BYTE+addr+1,(eip+1+DATA_BYTE+addr+1)-0x100000);
	 if(cpu.eflags.PF==1)
		 return 1+1+DATA_BYTE+addr;
	 else
		 return 1+DATA_BYTE+1;
 }
 make_helper(concat(jcc_js_,SUFFIX)){
	 DATA_TYPE addr;
	 addr=instr_fetch(eip+1+1,DATA_BYTE);
	 print_asm("js %x <main+0x%x>",eip+1+DATA_BYTE+addr+1,(eip+1+DATA_BYTE+addr+1)-0x100000);
	 if(cpu.eflags.SF==1)
		 return 1+1+DATA_BYTE+addr;
	 else
		 return 1+DATA_BYTE+1;
 }
 make_helper(concat(imul_r2rm_,SUFFIX)){
	 ModR_M m;
	 m.val=instr_fetch(eip+1+1,1);
	 if(m.mod==3){
		 if(DATA_BYTE==1){ 
			 short result;
			 result=(short)REG(m.reg)*REG(m.R_M);
			 if(result<=0x00ff)
				 cpu.eflags.OF=cpu.eflags.CF=0;
			 REG(m.reg)=REG(m.reg)*REG(m.R_M);
		 }
		 else if(DATA_BYTE==2){
			 long result;
			 result=(long)(REG(m.reg)*REG(m.R_M));
			 if(result<=0x0000ffff)
				 cpu.eflags.OF=cpu.eflags.CF=0;
			 REG(m.reg)=REG(m.reg)*REG(m.R_M);
		 }  
		 else{
			 long long result;
			 result=(long long)(REG(m.reg)*REG(m.R_M));
			 if(result<=0x00000000ffffffff)
				 cpu.eflags.OF=cpu.eflags.CF=0;
			 REG(m.reg)=REG(m.reg)*REG(m.R_M);
	 	 } 
		 print_asm("imul" str(SUFFIX) " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
		 return 1+1+1;
 	 }
	 else{
		 swaddr_t addr;
		 int len=read_ModR_M(eip+1+1,&addr);
		 DATA_TYPE imm=swaddr_read(addr,DATA_BYTE);
	 	 if(DATA_BYTE==1 ){
			 short result;
			 result=(short)(REG(m.reg)*imm);
			 if(result<=0x00ff)
				 cpu.eflags.OF=cpu.eflags.CF=0;
			 REG(m.reg)=REG(m.reg)*imm;
		 }
		 else if(DATA_BYTE==2){
			 long result;
			 result=(long)(REG(m.reg)*imm);
			 if(result<=0x0000ffff)
				 cpu.eflags.OF=cpu.eflags.CF=0;
			 REG(m.reg)=REG(m.reg)*imm;
		 }
		 else{
			 long long result;
			 result=(long long)(REG(m.reg)*imm);
			 if(result<=0x00000000ffffffff)
				 cpu.eflags.OF=cpu.eflags.CF=0;
			 REG(m.reg)=REG(m.reg)*imm;
		 } 
		 print_asm("imul" str(SUFFIX) " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));
		 return 1+len+1;
	 }  
 }
 make_helper(concat(movsx_r2rm8_,SUFFIX)){
	 ModR_M m;
	 m.val=instr_fetch(eip+1+1,1);
	 if(m.mod==3){
		 if(DATA_BYTE==2){
			 DATA_TYPE imm=REG(m.R_M)&0x00ff;
			 imm=(short)imm;
			 if(imm<0)
				 imm=imm|0xff00;
			 REG(m.reg)=imm;
			 print_asm("movsbw"  " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
	 	 }
		 else{
			 DATA_TYPE imm=REG(m.R_M)&0x000000ff;
			 imm=(int)imm;
			 if(imm<0)
				 imm=imm|0xffffff00;
			 REG(m.reg)=imm;
			 print_asm("movsbl" " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
	 	 }
		 return 1+1+1;
	 } 
	 else{ 
		 swaddr_t addr;
		 int len=read_ModR_M(eip+1+1,&addr);
		 if(DATA_BYTE==2){
			 DATA_TYPE imm=(swaddr_read(addr,DATA_BYTE))&0x00ff;
			 imm=(short)imm;
			 if(imm<0)
				 imm=imm|0xff00;
			 REG(m.reg)=imm;
			 print_asm("movsbw" " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));
	 	 }
	 	 else{
			 DATA_TYPE imm=(swaddr_read(addr,DATA_BYTE))&0x000000ff;
			 imm=(int)imm;
			 if(imm<0)
				 imm=imm|0xffffff00;
			 REG(m.reg)=imm;
			 print_asm("movsbl" " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));
		 }
		 return 1+1+len;
	 }
 }
 make_helper(concat(movsx_r2rm_,SUFFIX)){
	 ModR_M m;
	 m.val=instr_fetch(eip+1+1,1);
	 if(m.mod==3){
		 DATA_TYPE imm=(REG(m.R_M))&0x0000ffff;
		 imm=(int)imm;
		 if(imm<0)
			 imm=imm|0xffff0000;
		 REG(m.reg)=imm;
		 print_asm("movswl" " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
		 return 1+1+1;
	 } 
	 else{
		 swaddr_t addr;
		 int len=read_ModR_M(eip+1+1,&addr);
		 DATA_TYPE imm=(MEM_R(addr))&0x0000ffff;
		 imm=(int)imm;
		 if(imm<0)
			 imm=imm|0xffff0000;
		 REG(m.reg)=imm;
		 printf("%s=%d,%%%s=%d\n",ModR_M_asm,MEM_R(addr),REG_NAME(m.reg),REG(m.reg));
		 print_asm("movswl" " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));
		 return 1+1+len;
	  }
 }
 make_helper(concat(movzx_r2rm8_,SUFFIX)){
	 ModR_M m;
	 m.val=instr_fetch(eip+1+1,1);
	 if(m.mod==3){
		 if(DATA_BYTE==2){
			 DATA_TYPE imm=REG(m.R_M)&0x00ff;
			 imm=(short)imm;
			 REG(m.reg)=imm;
		 }
		 else{
			 DATA_TYPE imm=REG(m.R_M)&0x000000ff;
			 imm=(int)imm;
			 REG(m.reg)=imm;
		 } 
		 print_asm("movzbw" " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
		 return 1+1+1;
	 }
	 else{
		 swaddr_t addr;
		 int len=read_ModR_M(eip+1+1,&addr);
		 if(DATA_BYTE==2){
			 DATA_TYPE imm=(swaddr_read(addr,DATA_BYTE))&0x00ff;
			 imm=(short)imm;
			 REG(m.reg)=imm;
	 	 } 
	 	 else{ 
			 DATA_TYPE imm=(swaddr_read(addr,DATA_BYTE))&0x000000ff;
			 imm=(int)imm;
			 REG(m.reg)=imm;
		 }
		 print_asm("movzbl" " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));
		 return 1+1+len;
	 }
 }
make_helper(concat(movzx_r2rm_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1+1,1);
	if(m.mod==3){
		DATA_TYPE imm=(REG(m.R_M))&0x0000ffff;
		imm=(int)imm;
		REG(m.reg)=imm;
		print_asm("movzwl" " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
		return 1+1+1;
	} 
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1+1,&addr);
		DATA_TYPE imm=(MEM_R(addr))&0x0000ffff;
		imm=(int)imm;
		REG(m.reg)=imm;
		print_asm("movzwl" " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));
		return 1+1+len;
	} 
}


#include "exec/template-end.h"


