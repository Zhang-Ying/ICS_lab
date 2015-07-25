#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(sub_rm2r_,SUFFIX)){
   	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	DATA_TYPE s;
	char t;
	if (m.mod==3){
		s=REG(m.R_M)-REG(m.reg);
		if(REG(m.R_M)<REG(m.reg)){
			cpu.eflags.CF=1;
			cpu.eflags.SF=1;
		}
		else{ 
			cpu.eflags.CF=0;
			cpu.eflags.SF=0;
		}
		if(s==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if((REG(m.R_M)>0&&REG(m.reg)<0&&s<0)||(REG(m.R_M)<0&&REG(m.reg)>0&&s>0))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		REG(m.R_M)=s;
		print_asm("sub" str(SUFFIX) " %%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));
		return 1+1;
	}
	else{ 
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE n=instr_fetch(eip+1+len,DATA_BYTE);
		s=n-REG(m.reg);
	 	if(n<REG(m.reg)){
			cpu.eflags.CF=1;
			cpu.eflags.SF=1;
		} 
		else{ 
			cpu.eflags.CF=0;
			cpu.eflags.SF=0;
		}
		if(s==0)													  
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if((REG(m.reg)>0&&n<0&&s<0)||(REG(m.reg)<0&&n>0&&s>0))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		MEM_W(addr,s);
		print_asm("sub" str(SUFFIX) " %%%s,%s",REG_NAME(m.reg),ModR_M_asm);
		return 1+len;
 	}  
}
make_helper(concat(sub_r2rm_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1+1,1);
	DATA_TYPE s;
	char t;
	if(m.mod==3){  
		s=REG(m.reg)-REG(m.R_M);
		if(REG(m.reg)<REG(m.R_M)){ 
			cpu.eflags.CF=1;
			cpu.eflags.SF=1;
		 }
		else{ 
			cpu.eflags.CF=0;
			cpu.eflags.SF=0;
		} 
		if(s==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if((REG(m.reg)>0&&REG(m.R_M)<0&&s<0)||(REG(m.reg)<0&&REG(m.R_M)>0&&s>0))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		REG(m.reg)=s;
 		print_asm("sub" str(SUFFIX) " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
		return 1+1+1;
 	}   
 	else{   
		swaddr_t addr;
		int len=read_ModR_M(eip+1+1,&addr);
		DATA_TYPE n=instr_fetch(eip+1+1+len,DATA_BYTE);
		s=REG(m.reg)-n;
		if(REG(m.reg)<n){
			cpu.eflags.CF=1;
			cpu.eflags.SF=1;
		}
		else{		 		
			cpu.eflags.CF=0;
			cpu.eflags.SF=0;
		}
		if(s==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if((REG(m.reg)>0&&n<0&&s<0)||(REG(m.reg)<0&&n>0&&s>0))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		REG(m.reg)=s;
		print_asm("sub" str(SUFFIX) " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));
		return 1+1+len;
	} 
}
make_helper(concat(sub_al_,SUFFIX)){
	DATA_TYPE imm=instr_fetch(eip+1,1);
	DATA_TYPE m=REG(0x0);
	DATA_TYPE s;
	char t;
	s=m-imm;
	if(m<imm){
		cpu.eflags.CF=1;
		cpu.eflags.SF=1;
	} 
	else{
		cpu.eflags.CF=0;
		cpu.eflags.SF=0;
	}
	if(s==0)
		cpu.eflags.ZF=1;
	else
		cpu.eflags.ZF=0;
	if((m>0&&imm<0&&s<0)||(m<0&&imm>0&&s>0))
		cpu.eflags.OF=1;
	else
		cpu.eflags.OF=0;
		t=s&0xff;
	t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
	cpu.eflags.PF=t&0x01;
	REG(0x0)=s;
	print_asm("sub" str(SUFFIX) " al,$0x%x",imm);
	return 1+DATA_BYTE;
}
make_helper(concat(sub_rm2i_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	DATA_TYPE imm;
	DATA_TYPE s;
	char t;
   	if(m.mod==3){
		imm=instr_fetch(eip+1+1,DATA_BYTE);
		s=REG(m.R_M)-imm;
		if(REG(m.R_M)<imm){
			cpu.eflags.CF=1;
			cpu.eflags.SF=1;
		} 
		else{
			cpu.eflags.CF=0;
			cpu.eflags.SF=0;
		}
		if(s==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if((REG(m.R_M)>0&&imm<0&&s<0)||(REG(m.R_M)<0&&imm>0&&s>0))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		REG(m.R_M)=s;
		print_asm("sub" str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M));
	 	return 1+1+DATA_BYTE;
 	}    
 	else{  
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		imm=instr_fetch(eip+1+len,DATA_BYTE);
		DATA_TYPE n=MEM_R(addr);
		s=n-imm;
		if(n<imm){
			cpu.eflags.CF=1;
			cpu.eflags.SF=1;
		}
		else{
			cpu.eflags.CF=0;
			cpu.eflags.SF=0;
		}
		if(s==0)
			cpu.eflags.ZF=1;
		else					
			cpu.eflags.ZF=0;
		if((n>0&&imm<0&&s<0)||(n<0&&imm>0&&s>0))			
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		MEM_W(addr,s);
		print_asm("sub" str(SUFFIX)" $0x%x,%s",imm,ModR_M_asm);
		return 1+1+len;
	} 
}
make_helper(concat(and_rm2i_,SUFFIX)){
	cpu.eflags.CF=0;
	cpu.eflags.OF=0;
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	DATA_TYPE result;
	char t;
 	if(m.mod==3){
		DATA_TYPE imm=instr_fetch(eip+1+1,DATA_BYTE);
		result=imm&REG(m.R_M);
		REG(m.R_M)=result;
		t=result&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(result==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		print_asm("and" str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M));
		return 1+1+DATA_BYTE;
	} 
	else{ 
		swaddr_t addr;
		int len=read_ModR_M(eip+1+1,&addr);
		DATA_TYPE imm=instr_fetch(eip+1+len,DATA_BYTE);
		DATA_TYPE n=swaddr_read(addr,DATA_BYTE);
		result=n&imm;
		MEM_W(addr,result);
		t=result&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(result==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		print_asm("and" str(SUFFIX) " $0x%x,%s",imm,ModR_M_asm);
		return 1+len+DATA_BYTE;
 	}
}
make_helper(concat(cmp_rm2i_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	long result;
	char t;
	DATA_TYPE s;
	if(m.mod==3){
		DATA_TYPE imm=instr_fetch(eip+1+1,DATA_BYTE);
		result=imm-REG(m.reg);
		s=imm-REG(m.reg);
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if(result==s+0x100000000)
   			cpu.eflags.CF=1;
	   	else
		  	cpu.eflags.CF=0;
        if(cpu.eflags.CF==1)
	        cpu.eflags.SF=1;
        else if(s<0)
	   		cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(cpu.eflags.CF==0&&s==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(cpu.eflags.CF==1)
			cpu.eflags.OF=0;
		else if(result!=s)
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		print_asm("cmp" str(SUFFIX) " 0x%x,%%%s",imm,REG_NAME(m.reg));
		return 1+1+DATA_BYTE;
	}  
 	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE imm=instr_fetch(eip+1+len,DATA_BYTE);
		result=swaddr_read(addr,4)-imm;
		s=swaddr_read(addr,4)-imm;
		if(swaddr_read(addr,4)<imm){
			cpu.eflags.CF=1;
			cpu.eflags.SF=1;
		}
		else{
			cpu.eflags.CF=0;
			cpu.eflags.SF=0;
		}
		if(s==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if((swaddr_read(addr,4)>0&&imm<0&&s<0)||(swaddr_read(addr,4)<0&&imm>0&&s>0))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		print_asm("cmp" str(SUFFIX) " 0x%x,%s",imm,ModR_M_asm);
		return 1+len+DATA_BYTE;
	}
}
make_helper(concat(adc_rm2i_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	long result;
	DATA_TYPE s;
	char t;
	if(m.mod==3){
		DATA_TYPE imm=instr_fetch(eip+1+1,DATA_BYTE);
		s=imm+REG(m.R_M)+cpu.eflags.CF;
		result=imm+REG(m.R_M)+cpu.eflags.CF;
		REG(m.R_M)=s;
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if(result==s+0x100000000)
			cpu.eflags.CF=1;
		else
			cpu.eflags.CF=0;
	    if(cpu.eflags.CF==1)
			cpu.eflags.SF=1;
		else if(s<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(cpu.eflags.CF==0&&s==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(cpu.eflags.CF==1)
			cpu.eflags.OF=0;
		else if(result!=s)
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		print_asm("adc" str(SUFFIX) " 0x%x,%%%s",imm,REG_NAME(m.R_M));
		return 1+1+DATA_BYTE;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE imm1=swaddr_read(addr,DATA_BYTE);
		DATA_TYPE imm2=instr_fetch(eip+1+len,DATA_BYTE);
		s=imm1+imm2+cpu.eflags.CF;
		result=imm1+imm2+cpu.eflags.CF;
		MEM_W(addr,s);
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if(result==s+0x100000000)
			cpu.eflags.CF=1;
		else
			cpu.eflags.CF=0;
		if(cpu.eflags.CF==1)
			cpu.eflags.SF=1;
		else if(s<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(cpu.eflags.CF==0&&s==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(cpu.eflags.CF==1)
			cpu.eflags.OF=0;
		else if(result!=s)
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		print_asm("adc" str(SUFFIX) " 0x%x,%s",imm2,ModR_M_asm);
		return 1+len+DATA_BYTE;
	}
}
make_helper(concat(or_rm2i_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	long result;
	DATA_TYPE s;
	char t;
	if(m.mod==3){
		DATA_TYPE imm=instr_fetch(eip+1+1,DATA_BYTE);
		REG(m.R_M)=REG(m.R_M)|imm;
		s=REG(m.R_M);
		result=REG(m.R_M);
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if(result==s+0x100000000)
			cpu.eflags.CF=1;
		else
			cpu.eflags.CF=0;
		if(cpu.eflags.CF==1)
			cpu.eflags.SF=1;
		else if(s<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(cpu.eflags.CF==0&&s==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(cpu.eflags.CF==1)
			cpu.eflags.OF=0;
		else if(result!=s)
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		print_asm("or" str(SUFFIX) " 0x%x,%s",imm,REG_NAME(m.R_M));
		return 1+1+DATA_BYTE;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE imm1=MEM_R(addr);
		DATA_TYPE imm2=instr_fetch(eip+1+len,DATA_BYTE);
		MEM_W(addr,imm1|imm2);
		s=imm1|imm2;
		result=imm1|imm2;
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if(result==s+0x100000000)
			cpu.eflags.CF=1;
		else
			cpu.eflags.CF=0;
		if(cpu.eflags.CF==1)
			cpu.eflags.SF=1;
		else if(s<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(cpu.eflags.CF==0&&s==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(cpu.eflags.CF==1)
			cpu.eflags.OF=0;
		else if(result!=s)
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		print_asm("or" str(SUFFIX) " 0x%x,%s",imm2,ModR_M_asm);
		return 1+len+DATA_BYTE;
	}
}
make_helper(concat(xor_rm2i_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	long result;
	DATA_TYPE s;
	char t;
	if(m.mod==3){
		DATA_TYPE imm=instr_fetch(eip+1+1,DATA_BYTE);
		REG(m.R_M)=REG(m.R_M)^imm;
		s=REG(m.R_M);
		result=REG(m.R_M);
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if(result==s+0x100000000)
			cpu.eflags.CF=1;
		else
			cpu.eflags.CF=0;
		if(cpu.eflags.CF==1)
			cpu.eflags.SF=1;
		else if(s<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(cpu.eflags.CF==0&&s==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(cpu.eflags.CF==1)
			cpu.eflags.OF=0;
		else if(result!=s+0x100000000)
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		print_asm("xor" str(SUFFIX) " 0x%x,%s",imm,REG_NAME(m.R_M));
		return 1+1+DATA_BYTE;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE imm1=MEM_R(addr);
		DATA_TYPE imm2=instr_fetch(eip+1+len,DATA_BYTE);
		MEM_W(addr,imm1^imm2);
		s=imm1^imm2;
		result=imm1^imm2;
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if(result==s+0x100000000)
			cpu.eflags.CF=1;
		else
			cpu.eflags.CF=0;
		if(cpu.eflags.CF==1)
			cpu.eflags.SF=1;
		else if(s<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;															
		if(cpu.eflags.CF==0&&s==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(cpu.eflags.CF==1)
			cpu.eflags.OF=0;
		else if(result!=s+0x100000000)
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		print_asm("xor" str(SUFFIX) " 0x%x,%s",imm2,ModR_M_asm);
		return 1+len+DATA_BYTE;
	}
}
make_helper(concat(add_rm2i_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	long result;
	DATA_TYPE s;
	char t;
	if(m.mod==3){
		DATA_TYPE imm=instr_fetch(eip+1+1,DATA_BYTE);
		s=imm+REG(m.R_M);
		result=imm+REG(m.R_M);
		REG(m.R_M)=s;
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if(result==s+0x100000000)
			cpu.eflags.CF=1;
		else
			cpu.eflags.CF=0;
		if(cpu.eflags.CF==1)
			cpu.eflags.SF=1;
		else if(s<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(cpu.eflags.CF==0&&s==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(cpu.eflags.CF==1)
			cpu.eflags.OF=0;
		else if(result!=s+0x100000000)
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		print_asm("add" str(SUFFIX) " 0x%x,%%%s",imm,REG_NAME(m.R_M));
		return 1+1+DATA_BYTE;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE imm1=swaddr_read(addr,DATA_BYTE);
		DATA_TYPE imm2=instr_fetch(eip+1+len,DATA_BYTE);
		s=imm1+imm2;
		result=imm1+imm2;	
		MEM_W(addr,s);
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if(result==s+0x100000000)
			cpu.eflags.CF=1;
		else
			cpu.eflags.CF=0;
		if(cpu.eflags.CF==1)
			cpu.eflags.SF=1;
		else if(s<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(cpu.eflags.CF==0&&s==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(cpu.eflags.CF==1)
			cpu.eflags.OF=0;
		else if(result!=s+0x100000000)
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		print_asm("add" str(SUFFIX) " 0x%x,%s",imm2,ModR_M_asm);
		return 1+len+DATA_BYTE;
	}
}
make_helper(concat(sbb_rm2i_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	DATA_TYPE imm;
	imm=instr_fetch(eip+1+1,1);
	DATA_TYPE s;
	char t;
	if(m.mod==3){
		s=REG(m.R_M)-imm-cpu.eflags.CF;
		if(s<0){
			cpu.eflags.CF=1;
			cpu.eflags.SF=1;
		}
		else{			
			cpu.eflags.CF=0;
			cpu.eflags.SF=0;
		}
		if(s==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if((REG(m.R_M)>0&&imm<0&&cpu.eflags.CF<0&&s<0)||(REG(m.R_M)<0&&imm>0&&cpu.eflags.CF<0&&s>0))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		REG(m.R_M)=s;
		print_asm("sbb" str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M));
		return 1+1+DATA_BYTE;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE n=instr_fetch(eip+1+len,DATA_BYTE);
		s=n-imm-cpu.eflags.CF;
		if(s<0){
			cpu.eflags.CF=1;
			cpu.eflags.SF=1;
		}
		else{
			cpu.eflags.CF=0;
			cpu.eflags.SF=0;
		}
		if(s==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;			
		if((swaddr_read(addr,4)>0&&imm<0&&s<0)||(swaddr_read(addr,4)<0&&imm>0&&s>0))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		MEM_W(addr,s);
		print_asm("sbb" str(SUFFIX)" $0x%x,%s",imm,ModR_M_asm);
		return 1+1+len;
	}
}

#include "exec/template-end.h"
					
		
		
