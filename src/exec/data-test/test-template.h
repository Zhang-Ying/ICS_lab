#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(test_r2i_,SUFFIX)){
	int reg_code = instr_fetch(eip,1) & 0x7;
	DATA_TYPE imm1 = instr_fetch(eip+1,DATA_BYTE);
	DATA_TYPE imm2 = REG(reg_code);
	DATA_TYPE result = imm1 & imm2;
	if(result>=0)
		cpu.eflags.SF=0;
	else 
		cpu.eflags.SF=1;
	if(result==0)
		cpu.eflags.ZF=1;
	else
		cpu.eflags.ZF=0;
	cpu.eflags.PF=!((result&1)^(result&2)^(result&4)^(result&8)^(result&16)^(result&32)^(result&64)^(result&128)^(result&256));
	cpu.eflags.OF=0;
	cpu.eflags.CF=0;
	print_asm("test" str(SUFFIX) " %%%s,$0x%x", REG_NAME(reg_code),imm1);
	return DATA_BYTE+1;
}
make_helper(concat(test_rm2i_,SUFFIX)){
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	if(m.mod==3 ){
		DATA_TYPE imm1 = instr_fetch(eip + 1 + 1,DATA_BYTE);
		DATA_TYPE imm2 = REG(m.R_M);
		DATA_TYPE result = imm1 & imm2;
		if(result>0)
			cpu.eflags.SF=0;
		else
			cpu.eflags.SF=1;
		if(result==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		cpu.eflags.PF=!((result&1)^(result&2)^(result&4)^(result&8)^(result&16)^(result&32)^(result&64)^(result&128)^(result&256));
		cpu.eflags.OF=0;
		cpu.eflags.CF=0;
		print_asm("test" str(SUFFIX) " %%%s,$0x%x", REG_NAME(m.R_M), imm1);
		return DATA_BYTE + 1 + 1;
	}
	else{
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
        DATA_TYPE imm2 = instr_fetch(eip + 1 + len, DATA_BYTE);
		DATA_TYPE imm1 = swaddr_read(addr,DATA_BYTE);
		DATA_TYPE result = imm1 & imm2;
		if(result>0)
			cpu.eflags.SF=0;
		else
			cpu.eflags.SF=1;
		if(result==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		cpu.eflags.PF=!((result&1)^(result&2)^(result&4)^(result&8)^(result&16)^(result&32)^(result&64)^(result&128)^(result&256));
		cpu.eflags.OF=0;
		cpu.eflags.CF=0;
		print_asm("test" str(SUFFIX) " $0x%x,$0x%x",imm1, imm2);
		return DATA_BYTE + len + 1;
	}  
}
make_helper(concat(test_rm2r_,SUFFIX)){
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	if (m.mod==3){
        DATA_TYPE imm1 = REG(m.R_M);
		DATA_TYPE imm2 = REG(m.reg);
		DATA_TYPE result = imm1 & imm2;
		if(result>0)
			cpu.eflags.SF=0;
		else
			cpu.eflags.SF=1;
		if(result==0)
			cpu.eflags.ZF=1;
		else 
			cpu.eflags.ZF=0;
		cpu.eflags.PF=!((result&1)^(result&2)^(result&4)^(result&8)^(result&16)^(result&32)^(result&64)^(result&128)^(result&256));
		cpu.eflags.CF=0;
		cpu.eflags.OF=0;
		print_asm("test" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.reg),REG_NAME(m.R_M));
		return 1 +1;
	}   
	else{
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		ModR_M n;
		n.val = instr_fetch(eip +1 +len,1);
		DATA_TYPE imm1 = swaddr_read(addr,DATA_BYTE);
		DATA_TYPE imm2 = REG(n.R_M);
		DATA_TYPE result = imm1 & imm2;
		if(result>0)
			cpu.eflags.SF=0;
		else
			cpu.eflags.SF=1;
		if(result==0)
			cpu.eflags.ZF=1;
		else 
			cpu.eflags.ZF=0;
		cpu.eflags.PF=!((result&1)^(result&2)^(result&4)^(result&8)^(result&16)^(result&32)^(result&64)^(result&128)^(result&256));
		cpu.eflags.CF=0;
		cpu.eflags.OF=0;
		print_asm("test" str(SUFFIX) "$0x%x,%%%s", imm1,REG_NAME(n.R_M));
		return DATA_BYTE + 1 + len;
	}  
}
make_helper(concat(idiv_ax2rm_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	if(m.mod==3){
 		DATA_TYPE imm1=REG(m.R_M);
		DATA_TYPE imm2=REG(0);
		DATA_TYPE imm3=REG(2);
		if(DATA_BYTE!=1){
			REG(0)=((imm3<<DATA_BYTE)+imm2)/imm1;
			REG(2)=((imm3<<DATA_BYTE)+imm2)%imm1;
	 	}
		else
			REG(0)=((imm2%imm1)<<DATA_BYTE)+imm2/imm1;
		print_asm("idiv" str(SUFFIX) " %%%s",REG_NAME(m.R_M));
		return 1+1;
	} 
	else{ 
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE imm1=swaddr_read(addr,DATA_BYTE);
		DATA_TYPE imm2=REG(0);
		DATA_TYPE imm3=REG(2);
		if(DATA_BYTE!=1){
			REG(0)=((imm3<<DATA_BYTE)+imm2)/imm1;
			REG(2)=((imm3<<DATA_BYTE)+imm2)%imm1;
		}
		else
			REG(0)=((imm2%imm1)<<DATA_BYTE)+imm2/imm1;
		print_asm("idiv" str(SUFFIX) " %s",ModR_M_asm);
		return 1+len;
	}
}
 make_helper(concat(imul_rm_,SUFFIX)){
	 ModR_M m;
	 m.val=instr_fetch(eip+1,1);
	 if(m.mod==3){
		 DATA_TYPE s=REG(m.R_M);
		 if(DATA_BYTE==1){
			 if((short)REG(0)*s<0x00ff)
				 cpu.eflags.CF=cpu.eflags.OF=0;
			 else
				 cpu.eflags.CF=cpu.eflags.OF=1;
			 REG(0)=REG(0)*s;
		 }
		 else if(DATA_BYTE==2){ 
			 long result;
			 result=(long)REG(0)*s;
			 if(result<=0x0000ffff)
				 cpu.eflags.OF=cpu.eflags.CF=0;
			 else
				 cpu.eflags.CF=cpu.eflags.OF=1;				 
			 REG(0)=REG(0)*s;
			 REG(2)=(result&0xffff0000)>>16;
		 }
		 else{
			 long long result;
			 result=(long long)REG(0)*s;
			 if(result<=0x00000000ffffffff)
				 cpu.eflags.CF=cpu.eflags.OF=0;
			 else
				 cpu.eflags.CF=cpu.eflags.OF=1;
			 REG(0)=REG(0)*s;
			 REG(2)=(result&0xffffffff00000000)>>32;
		 }
 		 print_asm("imul" str(SUFFIX) " %%%s",REG_NAME(m.R_M));
 		 return 1+1;
 	 } 
	 else{
		 swaddr_t addr;
		 int len=read_ModR_M(eip+1,&addr);
		 DATA_TYPE s=swaddr_read(addr,DATA_BYTE);
 		 if(DATA_BYTE==1){
			 if(REG(0)*s<0x00ff)
				 cpu.eflags.CF=cpu.eflags.OF=0;
			 REG(0)=REG(0)*s;
 	 	 }
  		 else if(DATA_BYTE==2){
			 long result;
			 result=(long)REG(0)*s;
			 if(result<=0x0000ffff)
				 cpu.eflags.OF=cpu.eflags.CF=0;
			 REG(0)=REG(0)*s;
			 REG(2)=(result&0xffff0000)>>16;
		 }
 		 else{
			 long long result;
			 result=(long long)REG(0)*s;
			 if(REG(0)*s<=0x00000000ffffffff)
				 cpu.eflags.CF=cpu.eflags.OF=0;
			 REG(0)=REG(0)*s;
			 REG(2)=(result&0xffffffff00000000)>>32;
 		 }
		 print_asm("imul" str(SUFFIX) " %s",ModR_M_asm);
 		 return 1+len;
 	 } 
 }
 make_helper(concat(not_rm_,SUFFIX)){
	 ModR_M m;
	 m.val=instr_fetch(eip+1,1);
	 if(m.mod==3){
		 REG(m.R_M)=~(REG(m.R_M));
		 print_asm("not" str(SUFFIX) " %%%s",REG_NAME(m.R_M));
		 return 1+1;
	 }
	 else{
		 swaddr_t addr;
		 int len=read_ModR_M(eip+1,&addr);
		 DATA_TYPE imm=swaddr_read(addr,DATA_BYTE);
		 MEM_W(addr,~imm);
		 print_asm("not" str(SUFFIX) " %s",ModR_M_asm);
		 return 1+len;
	 }
 }
 make_helper(concat(mul_ax2rm_,SUFFIX)){
	 ModR_M m;
	 m.val=instr_fetch(eip+1,1);
	 long long s;
	 if(m.mod==3){
		 if(DATA_BYTE==1){
			 MEM_W(cpu.eax,(DATA_TYPE_S)REG(0)*(DATA_TYPE_S)REG(m.R_M));
			 if(MEM_R(cpu.eax)<=0xff)
				 cpu.eflags.CF=cpu.eflags.OF=0;
			 else
				 cpu.eflags.CF=cpu.eflags.OF=1;
	 	 }
		 else if(DATA_BYTE==2){
			 MEM_W(cpu.edx,(DATA_TYPE_S)(REG(0)*REG(m.R_M))>>16);
			 MEM_W(cpu.eax,(DATA_TYPE_S)(REG(0)*REG(m.R_M))&0x0000ffff);
			 if(REG(2)==0)
				 cpu.eflags.CF=cpu.eflags.OF=0;
			 else
				 cpu.eflags.CF=cpu.eflags.OF=1;
		 } 
		 else{
			 s=REG(0)*REG(m.R_M);
			 MEM_W(cpu.edx,s>>32);
			 MEM_W(cpu.eax,s&0xffffffff);
			 if(REG(2)==0)
				 cpu.eflags.CF=cpu.eflags.OF=0;
			 else
				 cpu.eflags.CF=cpu.eflags.OF=1;
		 } 
		 print_asm("mul" str(SUFFIX) " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(0));
		 return 1+1;
	 } 
	 else{
		 swaddr_t addr;
		 int len=read_ModR_M(eip+1,&addr);
		 DATA_TYPE_S imm=MEM_R(addr);
		 if(DATA_BYTE==1){
			 MEM_W(cpu.eax,(DATA_TYPE_S)REG(0)*imm);
			 if(MEM_R(cpu.eax)<=0xff)
				 cpu.eflags.CF=cpu.eflags.OF=0;
			 else
				 cpu.eflags.CF=cpu.eflags.OF=1;
	 	 }
		 else if(DATA_BYTE==2){
			 MEM_W(cpu.edx,((DATA_TYPE_S)REG(0)*imm)>>16);
			 MEM_W(cpu.eax,((DATA_TYPE_S)REG(0)*imm)&0x0000ffff);
			 if(REG(2)==0)
				 cpu.eflags.CF=cpu.eflags.OF=0;
			 else
				 cpu.eflags.CF=cpu.eflags.OF=1;
	 	 }
		 else{
			 s=REG(0)*imm;
			 MEM_W(cpu.edx,s>>32);
			 MEM_W(cpu.eax,s&0xffffffff);
			 if(REG(2)==0)
				 cpu.eflags.CF=cpu.eflags.OF=0;
			 else
				 cpu.eflags.CF=cpu.eflags.OF=1;
		 } 
		 print_asm("mul" str(SUFFIX) " %s,%%%s",ModR_M_asm,REG_NAME(0));
		 return 1+len;
	 } 
 }
 make_helper(concat(neg_rm_,SUFFIX)){
	 ModR_M m;
	 char t;
	 m.val=instr_fetch(eip+1,1);
	 if(m.mod==3){
		 if(REG(m.R_M)==0){
			 cpu.eflags.CF=0;
			 cpu.eflags.ZF=1;
		 }
		 else{
			 cpu.eflags.CF=1;
			 cpu.eflags.ZF=0;
		 }
		 if(REG(m.R_M)!=0&&(-REG(m.R_M))==0)
			 cpu.eflags.OF=1;
		 else
			 cpu.eflags.OF=0;
		 if(REG(m.R_M)>0)
			 cpu.eflags.SF=1;
		 else
			 cpu.eflags.SF=0;
		 REG(m.R_M)=-(REG(m.R_M));
		 t=REG(m.R_M)&0xff;
		 t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		 cpu.eflags.PF=t&0x01;
		 print_asm("neg" str(SUFFIX) " %%%s",REG_NAME(m.R_M));
		 return 1+1;
	 }
	 else{
		 swaddr_t addr;
		 int len=read_ModR_M(eip+1,&addr);
		 DATA_TYPE imm=swaddr_read(addr,DATA_BYTE);
		 if(imm==0){
			 cpu.eflags.CF=0;
			 cpu.eflags.ZF=1;
		 }
		 else{
			 cpu.eflags.CF=1;
			 cpu.eflags.ZF=0;
		 }					
		 if(imm!=0&&(-imm)==0)
			 cpu.eflags.OF=1;
		 else
			 cpu.eflags.OF=0;
		 if(imm>0)
			 cpu.eflags.SF=1;
		 else
			 cpu.eflags.SF=0;
		 MEM_W(addr,-imm);
		 t=MEM_R(addr)&0xff;
		 t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		 cpu.eflags.PF=t&0x01;
		 print_asm("neg" str(SUFFIX) " %s",ModR_M_asm);
		 return 1+len;
	 }
 }
make_helper(concat(div_ax2rm_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	if(m.mod==3){ 
		DATA_TYPE_S imm1=REG(m.R_M);
		DATA_TYPE_S imm2=REG(0);
		DATA_TYPE_S imm3=REG(2);
		if(DATA_BYTE!=1){
			REG(0)=((imm3<<DATA_BYTE)+imm2)/imm1;
			REG(2)=((imm3<<DATA_BYTE)+imm2)%imm1;
		}	 
		else
			REG(0)=((imm2%imm1)<<DATA_BYTE)+imm2/imm1;
		print_asm("div" str(SUFFIX) " %%%s",REG_NAME(m.R_M));
		return 1+DATA_BYTE;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE_S imm1=swaddr_read(addr,DATA_BYTE);											
 		DATA_TYPE_S imm2=REG(0);
		DATA_TYPE_S imm3=REG(2);
		if(DATA_BYTE==1){
			REG(0)=((imm3<<DATA_BYTE)+imm2)/imm1;
			REG(2)=((imm3<<DATA_BYTE)+imm2)%imm1;
	 	}
		else
			REG(0)=((imm2%imm1)<<DATA_BYTE)+imm2/imm1;
		print_asm("div" str(SUFFIX) " %s",ModR_M_asm);
		return 1+len;
	} 
}

#include "exec/template-end.h"
