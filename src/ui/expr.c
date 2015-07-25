#include "common.h"
#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>
#include<stdlib.h>
#include<elf.h>
void load_table();
char* strtab;
Elf32_Sym* symtab;
int nr_symtab_entry;

enum {
	NOTYPE =0,plus,EQ,minus,multiple,divide,left_bracket,right_bracket,digit,mod,le,ge,left,right,g,l,ne,land,lor,not,and,or,xor,traverse,value,neg,hex,reg,symbol

	/* TODO: Add more token types */

};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules. 
	 * Pay attention to the precedence level of different rules.
	 */ 

	{" +",	NOTYPE},				// white space
	{"\\+", plus},
	{"==",EQ},
	{"\\-", minus},
	{"\\*", multiple},
	{"/", divide},
	{"\\(", left_bracket},
	{"\\)", right_bracket},
	{"0[xX][0-9A-Fa-f]+",hex},
	{"\[0-9]+", digit},
    {"\\$[A-Za-z]+",reg},
	{"\[A-Za-z]+",symbol},
	{"%",mod},
	{"<=",le},
    {">=",ge},
    {"<<",left},
    {">>",right},
    {">",g},
	{"<",l},
	{"!=",ne},
	{"&&",land},
	{"\\|\\|",lor},
	{"!",not},
	{"&",and},
	{"\\|",or},
	{"\\^",xor},
	{"~",traverse}
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for more times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i <  NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			test(0, "regex compilation failed: %s\n%s\n", error_msg, rules[i].regex);
	  	} 
	}  
}

typedef struct token {
	int type;
	char* str;
} Token;
typedef struct p{
	int num;
	int preference;
} st;
Token tokens[32];
int nr_token;

static bool make_token(char *e) {
	char* regex;
	int position = 0;
	int i;
	regmatch_t pmatch;
	nr_token = 0;
	while(e[position] != '\000') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
	 		if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;
				position+=substr_len;
				Log("match regex[%d] at position %d with len %d: %.*s", i, position, substr_len, substr_len, substr_start);
	 			/* TODO: Now a new token is recognized with rules[i]. 
				 * Add codes to perform some actions with this token.
	 			 */
	  			switch(rules[i].token_type) {
					case plus:
						tokens[nr_token].type=plus;
						nr_token++;
						break;
					case minus:
						if(nr_token==0||(tokens[nr_token-1].type!=digit&&tokens[nr_token-1].type!=right_bracket))
							tokens[nr_token].type=neg;
						else
							tokens[nr_token].type=minus;
						nr_token++;
						break;
					case multiple:
						if(nr_token==0||(tokens[nr_token-1].type!=digit&&tokens[nr_token-1].type!=right_bracket))
							tokens[nr_token].type=value;
						else
							tokens[nr_token].type=multiple;
						nr_token++;
						break;
					case divide:
						tokens[nr_token].type=divide;
						nr_token++;
						break;
					case left_bracket:
						tokens[nr_token].type=left_bracket;
						nr_token++;
						break;
					case right_bracket:
						tokens[nr_token].type=right_bracket;
						nr_token++;
						break;
					case EQ:
						tokens[nr_token].type=EQ;
						nr_token++;
						break;
					case NOTYPE:
						break;
					case value:
						tokens[nr_token].type=value;
						nr_token++;
						break;
					case not:
						tokens[nr_token].type=not;
						nr_token++;
						break;
					case traverse:
						tokens[nr_token].type=traverse;
						nr_token++;
						break;
					case mod:
						tokens[nr_token].type=mod;
						nr_token++;
						break;
					case left:
						tokens[nr_token].type=left;
						nr_token++;
						break;
					case right:
						tokens[nr_token].type=right;
						nr_token++;
						break;
					case g:
						tokens[nr_token].type=g;
                        nr_token++;
						break;
					case ge:
						tokens[nr_token].type=ge;
						nr_token++;
						break;
					case l:
						tokens[nr_token].type=l;
						nr_token++;
						break;
					case le:
						tokens[nr_token].type=le;
						nr_token++;
						break;
					case ne:
						tokens[nr_token].type=ne;
						nr_token++;
						break;
					case and:
						tokens[nr_token].type=and;
                        nr_token++;
						break;
					case xor:
						tokens[nr_token].type=xor;
						nr_token++;
						break;
					case or:
						tokens[nr_token].type=or;
						nr_token++;
						break;
					case lor:
						tokens[nr_token].type=lor;
						nr_token++;
						break;
					case land:
						tokens[nr_token].type=land;
						nr_token++;
						break;
					case digit:
						regex=substr_start;
						tokens[nr_token].type=digit;
						tokens[nr_token].str=regex;
						nr_token++;
						break;
					case hex:
						regex=substr_start;
					    tokens[nr_token].type=hex;
						tokens[nr_token].str=regex;
						nr_token++;
						break;
					case reg:
						tokens[nr_token].type=reg;
						if(strlen(e)>4)
							assert(0);
						tokens[nr_token].str=e+1;
						nr_token++;
						break;
					case symbol:
						regex=substr_start;
						tokens[nr_token].type=symbol;
						tokens[nr_token].str=regex;
						nr_token++;
						break;
					default: assert(0);
				}
                break;
	 		}
	  	}
		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
	  	}
	}  
	return true;
}
bool parentheses(int p,int q){
	if(tokens[p].type==left_bracket&&tokens[q].type==right_bracket){
		int i=0,j;
		for(j=p;j<=q;j++){
			if(tokens[j].type==left_bracket)
				i++;
			if(tokens[j].type==right_bracket)
				i--;
			if(i<0){
				printf("Bad expression!\n");
				assert(0);
	 	 	}
	 	} 
		if(i!=0){
			printf("Bad expression!\n");
			assert(0);
	 	}
		return true;
	} 
	else
		return false;
}
uint32_t eval(int p,int q){
	uint32_t val1,val2,val;
	int i=0,op,j=0,t=0,m=0,k=0;
	st s[32];
	for(;i<32;i++)
		s[i].preference=0;
	if(p>q){
		printf("Bad expression!\n");
		assert(0);
	} 
	else if(p==q){
		int d;
		if(tokens[p].type==digit)
			d=strtol(tokens[p].str,NULL,10);
		else if(tokens[p].type==hex)
			d=strtol(tokens[p].str,NULL,16);
		else if(tokens[p].type==symbol){
			load_table();
			Elf32_Sym* current=symtab;
			int i=0;
			int j=0;
			char* temp=tokens[p].str;
			while(*temp){
				temp=temp+1;
				j++;
			}
			while(i<nr_symtab_entry){
				if(strncmp(strtab+current[i].st_name,tokens[p].str,j)==0&&(current[i].st_info&0x0000000f)==STT_OBJECT)
					break;
				i++;
			}
			if((i==nr_symtab_entry)&&!(current[i].st_info==STT_OBJECT&&(strtab+current[i].st_name)==tokens[p].str)){
				printf("Have no such symbol!\n");
				assert(0);
			}
			return current[i].st_value;
		}
		else{
			if(strcmp(tokens[p].str,"eax")||strcmp(tokens[p].str,"EAX"))
				d=swaddr_read(cpu.eax,4);
		    else if(strcmp(tokens[p].str,"ebx")||strcmp(tokens[p].str,"EBX"))
				d=swaddr_read(cpu.ebx,4);
			else if(strcmp(tokens[p].str,"ecx")||strcmp(tokens[p].str,"ECX"))
				d=swaddr_read(cpu.ecx,4);
		    else if(strcmp(tokens[p].str,"edx")||strcmp(tokens[p].str,"EDX"))
				d=swaddr_read(cpu.edx,4);
		    else if(strcmp(tokens[p].str,"esi")||strcmp(tokens[p].str,"ESI"))
				d=swaddr_read(cpu.esi,4);
			else if(strcmp(tokens[p].str,"edi")||strcmp(tokens[p].str,"EDI"))
				d=swaddr_read(cpu.edi,4);
			else if(strcmp(tokens[p].str,"esp")||strcmp(tokens[p].str,"ESP"))
				d=swaddr_read(cpu.esp,4);
			else if(strcmp(tokens[p].str,"ebp")||strcmp(tokens[p].str,"EBP"))
				d=swaddr_read(cpu.ebp,4);
		    else if(strcmp(tokens[p].str,"eip")||strcmp(tokens[p].str,"EIP"))
				d=swaddr_read(cpu.eip,4);
			else if(strcmp(tokens[p].str,"ax")||strcmp(tokens[p].str,"AX"))
				d=swaddr_read(cpu.eax,2);
			else if(strcmp(tokens[p].str,"bx")||strcmp(tokens[p].str,"BX"))
				d=swaddr_read(cpu.ebx,2);
			else if(strcmp(tokens[p].str,"cx")||strcmp(tokens[p].str,"CX"))
				d=swaddr_read(cpu.ecx,2);
			else if(strcmp(tokens[p].str,"dx")||strcmp(tokens[p].str,"DX"))
				d=swaddr_read(cpu.edx,2);
			else if(strcmp(tokens[p].str,"sp")||strcmp(tokens[p].str,"SP"))
				d=swaddr_read(cpu.esp,2);
			else if(strcmp(tokens[p].str,"bp")||strcmp(tokens[p].str,"BP"))
				d=swaddr_read(cpu.ebp,2);
			else if(strcmp(tokens[p].str,"si")||strcmp(tokens[p].str,"SI"))
				d=swaddr_read(cpu.esi,2);
			else if(strcmp(tokens[p].str,"di")||strcmp(tokens[p].str,"DI"))
				d=swaddr_read(cpu.edi,2);
			else if(strcmp(tokens[p].str,"ip")||strcmp(tokens[p].str,"IP"))
				d=swaddr_read(cpu.eip,2);
			else if(strcmp(tokens[p].str,"al")||strcmp(tokens[p].str,"AL"))
				d=swaddr_read(cpu.eax,1);
			else if(strcmp(tokens[p].str,"bl")||strcmp(tokens[p].str,"BL"))
				d=swaddr_read(cpu.ebx,1);
			else if(strcmp(tokens[p].str,"cl")||strcmp(tokens[p].str,"CL"))
				d=swaddr_read(cpu.ecx,1);
			else if(strcmp(tokens[p].str,"dl")||strcmp(tokens[p].str,"DL"))
				d=swaddr_read(cpu.edx,1);
			else if(strcmp(tokens[p].str,"ah")||strcmp(tokens[p].str,"AH"))
				d=swaddr_read(cpu.eax+2,1);
			else if(strcmp(tokens[p].str,"bh")||strcmp(tokens[p].str,"BH"))
				d=swaddr_read(cpu.ebx+2,1);
			else if(strcmp(tokens[p].str,"ch")||strcmp(tokens[p].str,"CH"))
				d=swaddr_read(cpu.ecx+2,1);
			else if(strcmp(tokens[p].str,"dh")||strcmp(tokens[p].str,"DH"))
				d=swaddr_read(cpu.edx+2,1);
			else{
				printf("No such register!\n");
				assert(0);
	 		}
		}
		return d;
	}
	else if(parentheses(p,q)==true){
		return eval(p+1,q-1);
	}
	else{
		k=0;
		for(op=p;op<=q;op++){
			if(tokens[op].type==plus||tokens[op].type==minus||tokens[op].type==multiple||tokens[op].type==divide||tokens[op].type==value||tokens[op].type==not||tokens[op].type==traverse||tokens[op].type==mod||tokens[op].type==left||tokens[op].type==right||tokens[op].type==g||tokens[op].type==ge||tokens[op].type==l||tokens[op].type==le||tokens[op].type==ne||tokens[op].type==and||tokens[op].type==xor||tokens[op].type==or||tokens[op].type==lor||tokens[op].type==land||tokens[op].type==EQ||tokens[op].type==neg){
					s[j].num=op;
					j++;
	 		}
	 	}
		int temp=j;
	   	for(t=0;t<temp;t++){
			if(tokens[s[t].num].type==lor)
				s[t].preference=0;
			else if(tokens[s[t].num].type==land)
				s[t].preference=1;
			else if(tokens[s[t].num].type==or)
				s[t].preference=2;
			else if(tokens[s[t].num].type==xor)
				s[t].preference=3;
			else if(tokens[s[t].num].type==and)
				s[t].preference=4;
			else if(tokens[s[t].num].type==EQ||tokens[s[t].num].type==ne)
				s[t].preference=5;
			else if(tokens[s[t].num].type==g||tokens[s[t].num].type==ge||tokens[s[t].num].type==l||tokens[s[t].num].type==le)
				s[t].preference=6;
			else if(tokens[s[t].num].type==left||tokens[s[t].num].type==right)
				s[t].preference=7;
			else if(tokens[s[t].num].type==plus||tokens[s[t].num].type==minus)
				s[t].preference=8;
		 	else if(tokens[s[t].num].type==multiple||tokens[s[t].num].type==divide)
				s[t].preference=9;
			else if(tokens[s[t].num].type==value||tokens[s[t].num].type==not||tokens[s[t].num].type==traverse||tokens[s[t].num].type==neg)
				s[t].preference=10;
	   	}
		for(;k<j;k++){
			for(t=p;t<=s[k].num-1;t++){
				if(tokens[t].type==left_bracket)
					m++;
				else if(tokens[t].type==right_bracket)
					m--;
				if(m<0){
					printf("Bad expression!\n");
					assert(0);
				}
	 		}
			if(m!=0)
				s[k].preference=-s[k].preference;
	 	}
		int pp=0;
		m=0;
	 	for(t=0;t<temp;t++){
			if(s[t].preference>0){
				if(s[t].preference<s[pp].preference)
					pp=t;
				m++;
			}
			if(m==0){
				if(s[t].preference>s[pp].preference)
					pp=t;
			}
		}
		op=s[pp].num;
		val2=eval(op+1,q);
		if(op!=0)
			val1=eval(p,op-1);
		else 
			val1=val2;
		switch(tokens[op].type){
			case plus:
				return val1+val2;
			case minus:
			    return val1-val2;
		    case multiple:
			    return val1*val2;
			case divide:
				return val1/val2;
			case mod:
				return val1%val2;
			case left:
				return val1<<val2;
			case right:
				return val1>>val2;
			case g:
				return val1>val2;
			case ge:
				return val1>=val2;
			case l:
				return val1<val2;
			case le:
				return val1<=val2;
			case ne:
				return val1!=val2;
			case and:
				return val1&val2;
			case xor:
				return val1^val2;
			case or:
				return val1|val2;
			case lor:
				return val1||val2;
			case land:
				return val1&&val2;
			case EQ:
				return val1==val2;
			case value:
				val=swaddr_read(val2,1);
				return val;
			case not:
				if(val2==0)
					return 1;
				else
					return 0;
			case traverse:
				return ~val2;
			case neg:
				return -val2;
			default:
				return 0;
		}		
	} 
}

uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
 	} 

	/* TODO: Implement code to evaluate the expression. */
	else
		return eval(0,nr_token-1);
} 

