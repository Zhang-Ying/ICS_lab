#include "exec/helper.h"

#define DATA_BYTE 1
#include "jcc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jcc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jcc-template.h"
#undef DATA_BYTE



extern char suffix;

make_helper(jcc_je){
	 swaddr_t addr;
	 addr=instr_fetch(eip+1,1);
	 if(addr>=0x80)
		 addr=-(0xff+1-addr);
	 print_asm("je %x <main+0x%x>",eip+1+1+addr,(eip+1+1+addr)-0x100000);
	 if(cpu.eflags.ZF==1){
		 cpu.eip+= 1 + 1 + addr;
		 return 0;
	 }
	 else
		 return 1 + 1;
}
make_helper(jcc_jbe){
	swaddr_t addr;
	addr=instr_fetch(eip+1,1);
	if(addr>=0x80)
		addr=-(0xff+1-addr);
	print_asm("jbe %x <main+0x%x>",eip+1+1+addr,(eip+1+1+addr)-0x100000);
	if(cpu.eflags.ZF==1||cpu.eflags.CF==1){
		cpu.eip+=1+1+addr;
		return 0;
	}
	else
		return 1+1;
}
make_helper(jcc_jle){
	swaddr_t addr;
	addr=instr_fetch(eip+1,1);
	if(addr>=0x80)
		addr=-(0xff+1-addr);
	print_asm("jle %x <main+0x%x>",eip+1+1+addr,(eip+1+1+addr)-0x100000);
	if(cpu.eflags.ZF==1||cpu.eflags.SF!=cpu.eflags.OF){
		cpu.eip+=1+1+addr;
		return 0;
	}
	else
		return 1+1;
}
make_helper(jcc_jge){
	swaddr_t addr;
	addr=instr_fetch(eip+1,1);
	if(addr>=0x80)
		addr=-(0xff+1-addr);
	print_asm("jge %x <main+0x%x>",eip+1+1+addr,(eip+1+1+addr)-0x100000);
	if(cpu.eflags.SF==cpu.eflags.OF||cpu.eflags.ZF==1){
		cpu.eip+=1+1+addr;
		return 0;
	}
	else
		return 1+1;
}
make_helper(jcc_jl){
	swaddr_t addr;
	addr=instr_fetch(eip+1,1);
	if(addr>=0x80)
		addr=-(0xff+1-addr);
	print_asm("jl %x <main+0x%x>",eip+1+1+addr,(eip+1+1+addr)-0x100000);
	if(cpu.eflags.SF!=cpu.eflags.OF&&cpu.eflags.ZF==0){
		cpu.eip+=1+1+addr;
		return 0;
	}
	else
		return 1+1;
}
make_helper(jcc_jo){
	swaddr_t addr;
	addr=instr_fetch(eip+1,1);
    if(addr>=0x80)
		addr=-(0xff+1-addr);
	print_asm("jo %x <main+0x%x>",eip+1+1+addr,(eip+1+1+addr)-0x100000);
	if(cpu.eflags.OF==1){
		cpu.eip+=1+1+addr;
		return 0;
	}
	else 
		return 1+1;
}
 make_helper(jcc_jno){
	 swaddr_t addr;
	 addr=instr_fetch(eip+1,1);
	 if(addr>=0x80)
		 addr=-(0xff+1-addr);
	 print_asm("jno %x <main+0x%x>",eip+1+1+addr,(eip+1+1+addr)-0x100000);
	 if(cpu.eflags.OF==0){
		 cpu.eip+=1+1+addr;
		 return 0;
	 }
	 else
		 return 1+1;
 }
 make_helper(jcc_jb){
	 swaddr_t addr;
	 addr=instr_fetch(eip+1,1);
	 if(addr>=0x80)
		 addr=-(0xff+1-addr);
	 print_asm("jb %x <main+0x%x>",eip+1+1+addr,(eip+1+1+addr)-0x100000);
	 if(cpu.eflags.CF==1){
		 cpu.eip+=1+1+addr;
		 return 0;
	 }
	 else
		 return 1+1;
 }
 make_helper(jcc_jae){
	 swaddr_t addr;
	 addr=instr_fetch(eip+1,1);
	 if(addr>=0x80)
		 addr=-(0xff+1-addr);
	 print_asm("jae %x <main+0x%x>",eip+1+1+addr,(eip+1+1+addr)-0x100000);
	 if(cpu.eflags.CF==0){
		 cpu.eip+=1+1+addr;
		 return 0;
	 }
	 else
		 return 1+1;
 }
 make_helper(jcc_jne){
	 swaddr_t addr;
	 addr=instr_fetch(eip+1,1);
	 if(addr>=0x80)
		 addr=-(0xff+1-addr);
	 print_asm("jne %x <main+0x%x>",eip+1+1+addr,(eip+1+1+addr)-0x100000);
	 if(cpu.eflags.ZF==0){
		 cpu.eip+=1+1+addr;
		 return 0;
	 }
	 else
		 return 1+1;
 }
 make_helper(jcc_ja){
	 swaddr_t addr;
	 addr=instr_fetch(eip+1,1);
	 if(addr>=0x80)
		 addr=-(0xff+1-addr);
	 print_asm("ja %x <main+0x%x>",eip+1+1+addr,(eip+1+1+addr)-0x100000);
	 if(cpu.eflags.CF==0&&cpu.eflags.ZF==0){
		 cpu.eip+=1+1+addr;
		 return 0;
	 }
	 else
		 return 1+1;
 }
 make_helper(jcc_js){
	 swaddr_t addr;
	 addr=instr_fetch(eip+1,1);
	 if(addr>=0x80)
		 addr=-(0xff+1-addr);
	 print_asm("js %x <main+0x%x>",eip+1+1+addr,(eip+1+1+addr)-0x100000);
	 if(cpu.eflags.SF==1){
		 cpu.eip+=1+1+addr;
		 return 0;
	 }
	 else
		 return 1+1;
 }
 make_helper(jcc_jns){
	 swaddr_t addr;
	 addr=instr_fetch(eip+1,1);
	 if(addr>=0x80)
		 addr=-(0xff+1-addr);
	 print_asm("jns %x <main+0x%x>",eip+1+1+addr,(eip+1+1+addr)-0x100000);
	 if(cpu.eflags.SF==0){
		 cpu.eip+=1+1+addr;
		 return 0;
	 }
	 else
		 return 1+1;
 }
 make_helper(jcc_jp){
	 swaddr_t addr;
	 addr=instr_fetch(eip+1,1);
	 if(addr>=0x80)
		 addr=-(0xff+1-addr);
	 print_asm("jp %x <main+0x%x>",eip+1+1+addr,(eip+1+1+addr)-0x100000);
	 if(cpu.eflags.PF==1){
		 cpu.eip+=1+1+addr;
		 return 0;
	 }
	 else
		 return 1+1;
 }
 make_helper(jcc_jnp){
	 swaddr_t addr;
	 addr=instr_fetch(eip+1,1);
	 if(addr>=0x80)
		 addr=-(0xff+1-addr);
	 print_asm("jnp %x <main+0x%x>",eip+1+1+addr,(eip+1+1+addr)-0x100000);
	 if(cpu.eflags.PF==0){
		 cpu.eip+=1+1+addr;
		 return 0;
	 }
	 else
		 return 1+1;
 }
 make_helper(jcc_jg){
	 swaddr_t addr;
	 addr=instr_fetch(eip+1,1);
	 if(addr>=0x80)
		 addr=-(0xff+1-addr);
	 print_asm("jg %x <main+0x%x>",eip+1+1+addr,(eip+1+1+addr)-0x100000);
	 if(cpu.eflags.SF==cpu.eflags.OF&&cpu.eflags.ZF==0){
		 cpu.eip+=1+1+addr;
		 return 0;
	 }
	 else
		 return 1+1;
 }
 make_helper(jcc_jcxz){
	 swaddr_t addr;
	 addr=instr_fetch(eip+1,1);
	 if(addr>=0x80)
		 addr=-(0xff+1-addr);
	 print_asm("jcxz %x <main+0x%x>",eip+1+1+addr,(eip+1+1+addr)-0x100000);
	 if(cpu.ecx==0){
		 cpu.eip+=1+1+addr;
		 return 0;
	 } 
	 else
		 return 1+1;
 }
 make_helper(seta){
	 ModR_M m;
	 m.val=instr_fetch(eip+1+1,1);
	 if(m.mod==3){
		 if(cpu.eflags.CF==0&&cpu.eflags.ZF==0)
			 reg_l(m.R_M)=1;
		 else
			 reg_l(m.R_M)=0;
		 print_asm("seta" " %%%s",regsl[m.R_M]);
		 return 1+1+1;
	 }
	 else{
		 swaddr_t addr;
		 int len=read_ModR_M(eip+1+1,&addr);
		 if(cpu.eflags.CF==0&&cpu.eflags.ZF==0)
			 swaddr_write(addr,4,1);
		 else
			 swaddr_write(addr,4,0);
		 print_asm("seta" " %s",ModR_M_asm);
		 return 1+1+len;
	 }
 }
make_helper(setae){
	ModR_M m;
	m.val=instr_fetch(eip+1+1,1);
	if(m.mod==3){
		if(cpu.eflags.CF==0)
			reg_l(m.R_M)=1;
		else
			reg_l(m.R_M)=0;
		print_asm("setae" " %%%s",regsl[m.R_M]);
		return 1+1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1+1,&addr);
		if(cpu.eflags.CF==0)
			swaddr_write(addr,4,1);
		else
			swaddr_write(addr,4,0);
		print_asm("setae" " %s",ModR_M_asm);
		return 1+1+len;
	}
}
make_helper(setb){
	ModR_M m;
	m.val=instr_fetch(eip+1+1,1);
	if(m.mod==3){
		if(cpu.eflags.CF==1)
			reg_l(m.R_M)=1;
		else
			reg_l(m.R_M)=0;
		print_asm("setb" " %%%s",regsl[m.R_M]);
		return 1+1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1+1,&addr);
		if(cpu.eflags.CF==1)
			swaddr_write(addr,4,1);
		else
			swaddr_write(addr,4,0);
		print_asm("setb" " %s",ModR_M_asm);
		return 1+1+len;
	}
}
make_helper(setbe){
	ModR_M m;
	m.val=instr_fetch(eip+1+1,1);
	if(m.mod==3){
		if(cpu.eflags.CF==1||cpu.eflags.ZF==0)
			reg_l(m.R_M)=1;
		else
			reg_l(m.R_M)=0;
		print_asm("setbe" " %%%s",regsl[m.R_M]);														
		return 1+1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1+1,&addr);
		if(cpu.eflags.CF==1||cpu.eflags.ZF==0)
			swaddr_write(addr,4,1);
		else
			swaddr_write(addr,4,0);
		print_asm("setbe" " %s",ModR_M_asm);
		return 1+1+len;
	}
}
make_helper(sete){
	ModR_M m;
	m.val=instr_fetch(eip+1+1,1);
	if(m.mod==3){
		if(cpu.eflags.ZF==1)
			reg_l(m.R_M)=1;
		else
			reg_l(m.R_M)=0;
		print_asm("sete" " %%%s",regsl[m.R_M]);
		return 1+1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1+1,&addr);
		if(cpu.eflags.ZF==1)
			swaddr_write(addr,4,1);
		else
			swaddr_write(addr,4,0);
		print_asm("sete" " %s",ModR_M_asm);
		return 1+1+len;
	}
}
make_helper(setg){
	ModR_M m;
	m.val=instr_fetch(eip+1+1,1);
	if(m.mod==3){
		if(cpu.eflags.SF==cpu.eflags.OF&&cpu.eflags.ZF==0)
			reg_l(m.R_M)=1;
		else
			reg_l(m.R_M)=0;
		print_asm("setg" " %%%s",regsl[m.R_M]);
		return 1+1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1+1,&addr);
		if(cpu.eflags.SF==cpu.eflags.OF&&cpu.eflags.ZF==0)
			swaddr_write(addr,4,1);
		else
			swaddr_write(addr,4,0);
		print_asm("setg" " %s",ModR_M_asm);
		return 1+1+len;
	}
}
make_helper(setge){
	ModR_M m;
	m.val=instr_fetch(eip+1+1,1);
	if(m.mod==3){
		if(cpu.eflags.SF==cpu.eflags.OF)
			reg_l(m.R_M)=1;
		else
			reg_l(m.R_M)=0;
		print_asm("setge" " %%%s",regsl[m.R_M]);
		return 1+1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1+1,&addr);
		if(cpu.eflags.SF==cpu.eflags.OF)
			swaddr_write(addr,4,1);
		else
			swaddr_write(addr,4,0);
		print_asm("setge" " %s",ModR_M_asm);
		return 1+1+len;
	}
}
make_helper(setl){
	ModR_M m;
	m.val=instr_fetch(eip+1+1,1);
	if(m.mod==3){
		if(cpu.eflags.SF!=cpu.eflags.OF)
			reg_l(m.R_M)=1;
		else
			reg_l(m.R_M)=0;
		print_asm("setl" " %%%s",regsl[m.R_M]);
		return 1+1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1+1,&addr);
		if(cpu.eflags.SF!=cpu.eflags.OF)
			swaddr_write(addr,4,1);
		else
			swaddr_write(addr,4,0);
		print_asm("setl" " %s",ModR_M_asm);
		return 1+1+len;
	}
}
make_helper(setle){
	ModR_M m;
	m.val=instr_fetch(eip+1+1,1);
	if(m.mod==3){
		if(cpu.eflags.SF!=cpu.eflags.OF&&cpu.eflags.ZF==1)
			reg_l(m.R_M)=1;
		else
			reg_l(m.R_M)=0;
		print_asm("setle" " %%%s",regsl[m.R_M]);
		return 1+1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1+1,&addr);
		if(cpu.eflags.SF!=cpu.eflags.OF&&cpu.eflags.ZF==1)
			swaddr_write(addr,4,1);
		else
			swaddr_write(addr,4,0);
		print_asm("setle" " %s",ModR_M_asm);
		return 1+1+len;
	}
}
make_helper(setne){
	ModR_M m;
	m.val=instr_fetch(eip+1+1,1);
	if(m.mod==3){
		if(cpu.eflags.ZF==0)
			reg_l(m.R_M)=1;
		else
			reg_l(m.R_M)=0;
		print_asm("setne" " %%%s",regsl[m.R_M]);
		return 1+1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1+1,&addr);
		if(cpu.eflags.ZF==0)
			swaddr_write(addr,4,1);
		else
			swaddr_write(addr,4,0);
		print_asm("setne" " %s",ModR_M_asm);
		return 1+1+len;
	}
}
make_helper(setno){
	ModR_M m;
	m.val=instr_fetch(eip+1+1,1);
	if(m.mod==3){
		if(cpu.eflags.OF==0)
			reg_l(m.R_M)=1;
		else
			reg_l(m.R_M)=0;
		print_asm("setno" " %%%s",regsl[m.R_M]);
		return 1+1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1+1,&addr);
		if(cpu.eflags.OF==0)
			swaddr_write(addr,4,1);
		else
			swaddr_write(addr,4,0);
		print_asm("setno" " %s",ModR_M_asm);
		return 1+1+len;
	}
}
make_helper(setnp){
	ModR_M m;
	m.val=instr_fetch(eip+1+1,1);
	if(m.mod==3){
		if(cpu.eflags.PF==0)
			reg_l(m.R_M)=1;
		else
			reg_l(m.R_M)=0;
		print_asm("setnp" " %%%s",regsl[m.R_M]);
		return 1+1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1+1,&addr);
		if(cpu.eflags.PF==0)
			swaddr_write(addr,4,1);
		else
			swaddr_write(addr,4,0);
		print_asm("setnp" " %s",ModR_M_asm);
		return 1+1+len;
	}
}
make_helper(setns){
	ModR_M m;
	m.val=instr_fetch(eip+1+1,1);
	if(m.mod==3){
		if(cpu.eflags.SF==0)
			reg_l(m.R_M)=1;
		else
			reg_l(m.R_M)=0;
		print_asm("setns" " %%%s",regsl[m.R_M]);
		return 1+1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1+1,&addr);
		if(cpu.eflags.SF==0)
			swaddr_write(addr,4,1);
		else
			swaddr_write(addr,4,0);
		print_asm("setns" " %s",ModR_M_asm);
		return 1+1+len;
	}
}
make_helper(seto){
	ModR_M m;
	m.val=instr_fetch(eip+1+1,1);
	if(m.mod==3){
		if(cpu.eflags.OF==1)
			reg_l(m.R_M)=1;
		else
			reg_l(m.R_M)=0;
		print_asm("seto" " %%%s",regsl[m.R_M]);
		return 1+1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1+1,&addr);
		if(cpu.eflags.OF==1)
			swaddr_write(addr,4,1);
		else
			swaddr_write(addr,4,0);
		print_asm("seto" " %s",ModR_M_asm);
		return 1+1+len;
	}
}
make_helper(setp){
	ModR_M m;
	m.val=instr_fetch(eip+1+1,1);
	if(m.mod==3){
		if(cpu.eflags.PF==1)
			reg_l(m.R_M)=1;
		else
			reg_l(m.R_M)=0;
		print_asm("setp" " %%%s",regsl[m.R_M]);
		return 1+1+1;
	} 
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1+1,&addr);
		if(cpu.eflags.PF==1)
			swaddr_write(addr,4,1);
		else
			swaddr_write(addr,4,0);
		print_asm("setp" " %s",ModR_M_asm);
		return 1+1+len;
	}
}
make_helper(lgdt){
	swaddr_t addr;
	addr=instr_fetch(eip+1+1+1,4);
	cpu.GDTR.base=swaddr_read(addr,4);
	print_asm("lgdt" str(SUFFIX) "0x%x",addr);
	return 1+1+1+4;
}
make_helper(mov_r2cr){
   ModR_M m;
   m.val=instr_fetch(eip+1+1,1);
   reg_l(m.reg)=(cpu.CR0.PE<<31)+(cpu.CR0.MP<<30)+(cpu.CR0.EM<<29)+(cpu.CR0.TS<<28)+(cpu.CR0.ET<<27)+cpu.CR0.PG;
   print_asm("mov" str(SUFFIX) " CR0,%%%s",regsl[m.reg]);
   return 1+1+1;
}
make_helper(mov_cr2r){
	ModR_M m;
	m.val=instr_fetch(eip+1+1,1);
	cpu.CR0.PE=reg_l(m.reg)&0x80000000;
	cpu.CR0.MP=reg_l(m.reg)&0x40000000;
	cpu.CR0.EM=reg_l(m.reg)&0x20000000;
	cpu.CR0.TS=reg_l(m.reg)&0x10000000;
	cpu.CR0.ET=reg_l(m.reg)&0x08000000;
	cpu.CR0.PG=reg_l(m.reg)&0x00000001;
	print_asm("mov" str(SUFFIX) " %%%s,CR0",regsl[m.reg]);
	return 1+1+1;
}

make_helper(jcc_v){
	swaddr_t imm;
	imm=instr_fetch(eip+1,1);
	if(imm==0x8c){
		return suffix=='l'?jcc_jl_l(eip):jcc_jl_w(eip);
	}
	else if(imm==0x86){
		return suffix=='l'?jcc_jbe_l(eip):jcc_jbe_w(eip);
	}
	else if(imm==0x87){
		return suffix=='l'?jcc_ja_l(eip):jcc_ja_w(eip);
	}
	else if(imm==0x83){
		return suffix=='l'?jcc_jae_l(eip):jcc_jae_w(eip);
	}
	else if(imm==0x82){
		return suffix=='l'?jcc_jb_l(eip):jcc_jb_w(eip);
	}
	else if(imm==0x84){
		return suffix=='l'?jcc_je_l(eip):jcc_je_w(eip);
	}
	else if(imm==0x8f){
		return suffix=='l'?jcc_jg_l(eip):jcc_jg_w(eip);
	}
	else if(imm==0x8d){
		return suffix=='l'?jcc_jge_l(eip):jcc_jge_w(eip);
	}
	else if(imm==0x81){
		return suffix=='l'?jcc_jno_l(eip):jcc_jno_w(eip);
	}
	else if(imm==0x8e){
		return suffix=='l'?jcc_jle_l(eip):jcc_jle_w(eip);
	}
	else if(imm==0x85){
		return suffix=='l'?jcc_jne_l(eip):jcc_jne_w(eip);
	}
	else if(imm==0x8b){
		return suffix=='l'?jcc_jnp_l(eip):jcc_jnp_w(eip);
	}
	else if(imm==0x89){
		return suffix=='l'?jcc_jns_l(eip):jcc_jns_w(eip);
	}
	else if(imm==0x80){
		return suffix=='l'?jcc_jo_l(eip):jcc_jo_w(eip);
	}
	else if(imm==0x8a){
		return suffix=='l'?jcc_jp_l(eip):jcc_jp_w(eip);
	}
	else if(imm==0x88){
		return suffix=='l'?jcc_js_l(eip):jcc_js_w(eip);
  	}
	else if(imm==0xaf){
		return suffix=='l'?imul_r2rm_l(eip):imul_r2rm_w(eip);
	}
	else if(imm==0xbe){
		return suffix=='l'?movsx_r2rm8_l(eip):movsx_r2rm8_w(eip);
	}
	else if(imm==0xbf){
		return movsx_r2rm_l(eip);
	}
	else if(imm==0xb6){
		return suffix=='l'?movzx_r2rm8_l(eip):movzx_r2rm8_w(eip);
	}
	else if(imm==0xb7){
		return movzx_r2rm_l(eip);
	}
	else if(imm==0x97){
		return seta(eip);
	}
	else if(imm==0x93){
		return setae(eip);
	}
	else if(imm==0x92){
		return setb(eip);
	}
	else if(imm==0x96){
		return setbe(eip);
	}
	else if(imm==0x94){
		return sete(eip);
	}
	else if(imm==0x9f){
		return setg(eip);
	}
	else if(imm==0x9d){
		return setge(eip);
	}
	else if(imm==0x9c){
		return setl(eip);
	}
	else if(imm==0x9e){
		return setle(eip);
	}
	else if(imm==0x95){
		return setne(eip);
	}
	else if(imm==0x91){
		return setno(eip);
	}
	else if(imm==0x9b){
		return setnp(eip);
	}
	else if(imm==0x99){
		return setns(eip);
	}
	else if(imm==0x90){
		return seto(eip);
	}
	else if(imm==0x9a){
		return setp(eip);
	}
	else if(imm==0x01){
		ModR_M m;
		m.val=instr_fetch(eip+1+1,1);
		if(m.reg==0x2)
			return lgdt(eip);
		else 
			return 0;
	}
	else if(imm==0x20)
		return mov_r2cr(eip);
	else if(imm==0x22)
		return mov_cr2r(eip);
	else
		return 0;
}


