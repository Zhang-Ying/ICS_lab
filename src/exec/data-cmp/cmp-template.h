#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(cmp_rm2ie_,SUFFIX)){
	ModR_M m;
	DATA_TYPE imm1;
	DATA_TYPE imm2;
	DATA_TYPE result;
	char t;
	m.val=instr_fetch(eip+1,1);
	if(m.mod==3){  
		DATA_TYPE imm1=instr_fetch(eip+1+1,1);
		if( DATA_BYTE==2&&imm1>>7!=0){
			 imm1=(short)imm1;
			 imm1=0xFF00+imm1;
	   	}
		else  if(DATA_BYTE==4&&imm1>>7!=0){
			 imm1=(int)imm1;
   			 imm1=0xFFFFFF00+imm1;
		 }
	   	else if(DATA_BYTE==2)
			imm1=(short)imm1;
		else
			imm1=(int)imm1;
		imm2=REG(m.R_M&111);
		result=imm1-imm2;
 		t=result&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if((imm1<0&&imm2>0&&result>0)||(imm1>0&&imm2<0&&result<0))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		if(imm1<imm2)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(result==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
       if(imm1<imm2)
		   cpu.eflags.CF=1;
	   else 
		   cpu.eflags.CF=0;
	   print_asm("cmp" str(SUFFIX) " $0x%x,%%%s", imm1,REG_NAME(m.R_M&7));
	   return 1+1+1;
 	} 
	else{ 
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		imm1=instr_fetch(eip+len+1,1);
		if ( DATA_BYTE==2&&imm1>>7!=0){
			imm1=(short)imm1;
			imm1=0xFF00+imm1;
		}
		else  if(DATA_BYTE==4&&imm1>>7!=0){
			imm1=(int)imm1;
			imm1=0xFFFFFF00+imm1;
		}
		else if(DATA_BYTE==2)
			imm1=(short)imm1;
		else
			imm1=(int)imm1;
		imm2=swaddr_read(addr,DATA_BYTE);
		result=imm2-imm1;
 		t=result&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if((imm1<0&&imm2>0&&result>0)||(imm1>0&&imm2<0&&result<0))
		    cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
	    if(imm2<imm1)
			cpu.eflags.SF=1;
	    else
			cpu.eflags.SF=0;
	    if(result==0)
		    cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(imm2<imm1)
			cpu.eflags.CF=1;
		else
			cpu.eflags.CF=0;
		print_asm("cmp"str(SUFFIX) " $0x%x,%s",imm1,ModR_M_asm);
		return 1+len+1;
	}    
}
make_helper(concat(cmp_rm2r_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	DATA_TYPE s;
	char t;
	if(m.mod==3) {
		DATA_TYPE imm=REG(m.R_M);
		s=imm-REG(m.reg);
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if((imm<0&&REG(m.reg)>0&&s>0)||(imm>0&&REG(m.reg)<0&&s<0))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		if(imm<REG(m.reg))
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(s==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(imm<REG(m.reg))
			cpu.eflags.CF=1;
		else																							
   			cpu.eflags.CF=0;
		printf("%%%s=%d,%%%s=%d\n",REG_NAME(m.reg),REG(m.reg),REG_NAME(m.R_M),REG(m.R_M));
		print_asm("cmp" str(SUFFIX) " %%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));
		return 1+1;
	}
	else{ 
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE imm1,imm2;
		imm1=swaddr_read(addr,DATA_BYTE);
		imm2=REG(m.reg);
		s=imm1-imm2;
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if((imm1<0&&imm2>0&&s>0)||(imm1>0&&imm2<0&&s<0))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		if(imm1<imm2)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(s==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(imm1<imm2)
			cpu.eflags.CF=1;
		else
			cpu.eflags.CF=0;
		print_asm("cmp" str(SUFFIX) "%%%s,%s",REG_NAME(m.reg),ModR_M_asm);
		return 1+len;
	} 
}
make_helper(concat(cmp_r2rm_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	DATA_TYPE imm=REG(m.reg);
	DATA_TYPE s;
	char t;
	if(m.mod==3){ 
		DATA_TYPE imm1=REG(m.R_M);
		s=imm-imm1;
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if((imm<0&&imm1>0&&s>0)||(imm>0&&imm1<0&&s<0))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		if(imm<imm1)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(s==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(imm<imm1)
			cpu.eflags.CF=1;		
		else
			cpu.eflags.CF=0;
        print_asm("cmp" str(SUFFIX) " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
		return 1+1;
	}
	else { 
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE imm1=swaddr_read(addr,DATA_BYTE);
		s=imm-imm1;
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if((imm<0&&imm1>0&&s>0)||(imm>0&&imm1<0&&s<0))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		if(imm<imm1)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(s==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(imm<imm1)
			cpu.eflags.CF=1;
		else
			cpu.eflags.CF=0;
		printf("%%%s=%d,%s=%d\n",REG_NAME(m.reg),REG(m.reg),ModR_M_asm,MEM_R(addr));
		print_asm("cmp" str(SUFFIX) " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));
		return 1+len;
	} 
}
make_helper(concat(cmp_al_,SUFFIX)){
	DATA_TYPE imm=instr_fetch(eip+1,DATA_BYTE);
	DATA_TYPE s;
	char t;
	if(DATA_BYTE==1)
		s=((REG(0))&0x000000FF)-imm;  
	else if(DATA_BYTE== 2)
		s=((REG(0))&0x0000FFFF)-imm;
	else
	    s=REG(0)-imm;
	t=s&0xff;
	t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
	cpu.eflags.PF=t&0x01;
	if((REG(0)<0&&imm>0&&s>0)||(REG(0)>0&&imm<0&&s<0))
		cpu.eflags.OF=1;
	else
		cpu.eflags.OF=0;
	if(REG(0)<imm)
		cpu.eflags.SF=1;
	else
		cpu.eflags.SF=0;
	if(s==0)
		cpu.eflags.ZF=1;
	else
		cpu.eflags.ZF=0;
	if(REG(0)<imm)
		cpu.eflags.CF=1;
	else
		cpu.eflags.CF=0;
  	print_asm("cmp" str(SUFFIX) " %x,%%%s",imm,REG_NAME(0));
	return 1+1;
}
make_helper(concat(sub_rm2ie_,SUFFIX)){
	ModR_M m;
	DATA_TYPE n;
	m.val=instr_fetch(eip+1,1);
	char t;
	DATA_TYPE s;
 	if(m.mod==3){ 
		int imm;
		DATA_TYPE imm1=instr_fetch(eip+1+1,1);
		if((imm1>>7)!=0)
			imm=0xffffff00+imm1;
		else
			imm=0x00000000+imm1;
		n=REG(m.R_M&111);
		s=n-imm;
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if((n<0&&imm>0&&s>0)||(n>0&&imm<0&&s<0))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		if(n<imm)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(s==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(n<imm)
			cpu.eflags.CF=1;
		else
			cpu.eflags.CF=0;
        REG(m.R_M&111)=s;
        print_asm("sub" str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M&111));
        return 1+1+1;
	}   
	else{ 
		int imm;
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE n=MEM_R(addr);
		DATA_TYPE imm1=instr_fetch(eip+1+len,1);
        if((imm1>>7)!=0)
			imm=0xffffff00+imm1;
		else
			imm=0x00000000+imm1;
		s=n-imm;
		t=s&0xff;
		t=(t>>1)^(t>>2)^(t>>3)^(t>>4)^(t>>5)^(t>>6)^(t>>7)^(t>>8);
		cpu.eflags.PF=t&0x01;
		if((n<0&&imm>0&&s>0)||(n>0&&imm<0&&s<0))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		if(n<imm)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(s==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		if(n<imm)
			cpu.eflags.CF=1;
		else
			cpu.eflags.CF=0;
		MEM_W(addr,s);
		print_asm("sub" str(SUFFIX)" $0x%x,%s",imm,ModR_M_asm);
		return 1+1+len;
	} 
}
make_helper(concat(and_rm2ie_,SUFFIX)){
	cpu.eflags.CF=0;
	cpu.eflags.OF=0;
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	DATA_TYPE result;
	if(m  .mod==3){
		DATA_TYPE imm=instr_fetch(eip+1+1,1);
		if(imm>>7!=0&&DATA_BYTE==2){
			imm=(short)imm;
			imm=imm+0xFF00;
		} 
		else if(imm>>7!=0&&DATA_BYTE==4){
			imm=(int)imm;
			imm=imm+0xFFFFFF00;
		}
		else if(DATA_BYTE==2)
			imm=(short)imm;
		else
			imm=(int)imm;
		result=imm&REG(m.R_M);
		REG(m.R_M)=result;
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(result==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		print_asm("and" str(SUFFIX) " 0x%x,%%%s",imm,REG_NAME(m.R_M));
		return 1+1+1;
	}  
 	else{
		swaddr_t addr;
		DATA_TYPE imm,n;
		int len=read_ModR_M(eip+1+1,&addr);
		imm=instr_fetch(eip+1+len,1);
		n=swaddr_read(addr,DATA_BYTE);
 		if(imm>>7!=0&&DATA_BYTE==2){
		   	imm=(short)imm;
            imm=imm+0xFF00;
	 	}
 	 	else if(imm>>7!=0&&DATA_BYTE==4){
			imm=(int)imm;
			imm=imm+0xFFFF0000;
		}  
		else if(DATA_BYTE==2)
			imm=(short)imm;
		else
			imm=(int)imm;
		result=imm&n;
		MEM_W(addr,result);
		if(result<0)
			cpu.eflags.SF=1;
		else
			cpu.eflags.SF=0;
		if(result==0)
			cpu.eflags.ZF=1;
		else
			cpu.eflags.ZF=0;
		print_asm("and" str(SUFFIX) " 0x%x,%s",imm,ModR_M_asm);
		return 1+len+DATA_BYTE;
	}    
}
make_helper(concat(add_rm2ie_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	DATA_TYPE s;
	long result;
	char t;
	if(m.mod==3){
		DATA_TYPE imm=instr_fetch(eip+1+1,1);
		if( imm<0&&DATA_BYTE==2){
			imm=(short)imm;
			imm=imm+0xFF00;
		}
		else  if(imm<0&&DATA_BYTE==4){
			imm=(int)imm;
			imm=imm+0xFFFFFF00;
		}
		else if(DATA_BYTE==2)
			imm=(short)imm;
		else
			imm=(int)imm;
		result=REG(m.R_M)+imm;
		s=REG(m.R_M)+imm;
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
		print_asm("add" str(SUFFIX) " %x,%%%s",imm,REG_NAME(m.R_M));
		return 1+1+1;
	}
 	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE n=swaddr_read(addr,DATA_BYTE);
		int imm=instr_fetch(eip+len+1,1);
 		if(imm<0&&DATA_BYTE==2){
			imm=(short)imm;
			imm=imm+0xFF00;
		}
 		else if(imm<0&&DATA_BYTE==4){
			imm=(int)imm;
			imm=imm+0xFFFFFF00;
		}
		else if(DATA_BYTE==2)
			imm=(short)imm;
		else
			imm=(int)imm;
		MEM_W(addr,n+imm);
		result=n+imm;
		s=n+imm;
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
		print_asm("add" str(SUFFIX) " %x,%s",imm,ModR_M_asm);
		return 1+len+1;
	} 
}
make_helper(concat(adc_rm2ie_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	DATA_TYPE s;
	long result;
	char t;
	if(m.mod==3){
		DATA_TYPE imm=instr_fetch(eip+1+1,DATA_BYTE);
		if(imm<0&&DATA_BYTE==2){
			imm=(short)imm;
			imm=imm+0xFF00;
		}
		else if(imm<0&&DATA_BYTE==4){
			imm=(int)imm;
			imm=imm+0xFFFFFF00;
		}
		else if(DATA_BYTE==2)
			imm=(short)imm;
		else
			imm=(int)imm;
		result=REG(m.R_M)+imm+cpu.eflags.CF;
		s=REG(m.R_M)+imm+cpu.eflags.CF;
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
		print_asm("adc" str(SUFFIX) " %x,%%%s",imm,REG_NAME(m.R_M));
		return 1+1+1;
	} 
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE n=swaddr_read(addr,DATA_BYTE);
		DATA_TYPE imm=instr_fetch(eip+len+1,1);
		if(imm<0&&DATA_BYTE==2){
			imm=(short)imm;
			imm=imm+0xFF00;
		}
		else if(imm<0&&DATA_BYTE==4){
			imm=(int)imm;
			imm=imm+0xFFFFFF00;
		}
		else if(DATA_BYTE==2)
			imm=(short)imm;
		else
			imm=(int)imm;
		MEM_W(addr,n+imm);
		result=n+imm+cpu.eflags.CF;
		s=n+imm+cpu.eflags.CF;
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
		print_asm("adc" str(SUFFIX) " %x,%s",imm,ModR_M_asm);
		return 1+len+1;
	} 
}
make_helper(concat(or_rm2ie_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	DATA_TYPE s;
	long result;
	char t;
	if(m.mod==3){
		DATA_TYPE imm=instr_fetch(eip+1+1,DATA_BYTE);
		if(imm<0&&DATA_BYTE==2){
			imm=(short)imm;
			imm=imm+0xFF00;
		}
		else if(imm<0&&DATA_BYTE==4){
			imm=(int)imm;
			imm=imm+0xFFFFFF00;
		}
		else if(DATA_BYTE==2)
			imm=(short)imm;
		else
			imm=(int)imm;
		result=REG(m.R_M)|imm;
		s=REG(m.R_M)|imm;
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
		print_asm("or" str(SUFFIX) " %x,%%%s",imm,REG_NAME(m.R_M));
		return 1+1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE n=swaddr_read(addr,DATA_BYTE);
		DATA_TYPE imm=instr_fetch(eip+len+1,1);
		if(imm<0&&DATA_BYTE==2){
			imm=(short)imm;
			imm=imm+0xFF00;
		}
		else if(imm<0&&DATA_BYTE==4){
			imm=(int)imm;
			imm=imm+0xFFFFFF00;
		}
		else if(DATA_BYTE==2)
			imm=(short)imm;
		else
			imm=(int)imm;
		MEM_W(addr,n+imm);
		result=n|imm;
		s=n|imm;
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
		print_asm("or" str(SUFFIX) " %x,%s",imm,ModR_M_asm);
		return 1+len+1;
	}
}
make_helper(concat(xor_rm2ie_,SUFFIX)){
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	DATA_TYPE s;
	long result;
	char t;
	if(m.mod==3){
		DATA_TYPE imm=instr_fetch(eip+1+1,DATA_BYTE);
		if(imm<0&&DATA_BYTE==2){
			imm=(short)imm;
			imm=imm+0xFF00;
		}
		else if(imm<0&&DATA_BYTE==4){
			imm=(int)imm;
			imm=imm+0xFFFFFF00;
		}
		else if(DATA_BYTE==2)
			imm=(short)imm;
		else
			imm=(int)imm;
		result=REG(m.R_M)^imm;
		s=REG(m.R_M)^imm;
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
		print_asm("xor" str(SUFFIX) " %x,%%%s",imm,REG_NAME(m.R_M));
		return 1+1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE n=swaddr_read(addr,DATA_BYTE);
		DATA_TYPE imm=instr_fetch(eip+len+1,1);
		if(imm<0&&DATA_BYTE==2){
			imm=(short)imm;
			imm=imm+0xFF00;
		}
		else if(imm<0&&DATA_BYTE==4){
			imm=(int)imm;
			imm=imm+0xFFFFFF00;
		}
		else if(DATA_BYTE==2)
			imm=(short)imm;
		else
			imm=(int)imm;
		MEM_W(addr,n+imm);
		result=n^imm;
		s=n^imm;
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
		print_asm("xor" str(SUFFIX) " %x,%s",imm,ModR_M_asm);
		return 1+len+1;
	}
}
make_helper(concat(sbb_rm2ie_,SUFFIX)){
	ModR_M m;
	DATA_TYPE n;
	m.val=instr_fetch(eip+1,1);
	int imm;
	DATA_TYPE imm1=instr_fetch(eip+1+1,1);
	if(imm1<0)
		imm=0x11111100+imm1;
	else
		imm=0x00000000+imm1;
	long result;
	DATA_TYPE s;
	if(m.mod==3){
		n=REG(m.R_M&111);
		s=n-imm-cpu.eflags.CF;
		result=n-imm-cpu.eflags.CF;
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
			REG(m.R_M&111)=s;
			print_asm("sbb" str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M&111));
			return 1+1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE n=instr_fetch(eip+1+len,DATA_BYTE);
		s=n-imm-cpu.eflags.CF;
		result=n-imm-cpu.eflags.CF;
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
		MEM_W(addr,s);
		print_asm("sbb" str(SUFFIX)" $0x%x,%s",imm,ModR_M_asm);
		return 1+1+len;
	}
}


#include "exec/template-end.h"
 
        

		

