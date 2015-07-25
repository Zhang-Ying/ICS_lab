#include "ui/ui.h"
#include "nemu.h"
#include<stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <elf.h>

int nemu_state = END;
char*strtab;
Elf32_Sym* symtab;
int nr_symtab_entry;

void cpu_exec(uint32_t);
void restart();
void breakpoint_start(uint32_t n);
void watchpoint_start(uint32_t n);
void init_bp_pool();
void breakpoint_del(int n);
void breakpoint_print();
uint32_t expr(char*,bool*);
bool make_token(char*);
/* We use the readline library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;
 	if (line_read) {
		free(line_read);
		line_read = NULL;
	} 

	line_read = readline("(nemu) ");

	if  (line_read && *line_read) {
		add_history(line_read);
 	}

	return line_read;
}

/* This function will be called when you press <C-c>. And it will return to 
 * where you press <C-c>. If you are interesting in how it works, please
 * search for "Unix signal" in the Internet.
 */
static void control_C(int signum) {
 	if(nemu_state == RUNNING) {
		nemu_state = INT;
	} 
}

void init_signal() {
	/* Register a signal handler. */
	struct sigaction s;
	memset(&s, 0, sizeof(s));
	s.sa_handler = control_C;
	int ret = sigaction(SIGINT, &s, NULL);
	assert(ret == 0);
}

static void cmd_c() {
	if (nemu_state == END) {
		puts("The Program does not start. Use 'r' command to start the program.");
		return;
 	}

	nemu_state = RUNNING;
	cpu_exec(-1);
	if(nemu_state != END) { nemu_state = STOP; }
}

static void cmd_r() {
	if(nemu_state != END) { 
		char c;
	 	while(1) {
			printf("The program is already running. Restart the program? (y or n)");
			fflush(stdout);
			scanf(" %c", &c);	
			switch(c) {
				case 'y': goto restart_;
				case 'n': return;
				default: puts("Please answer y or n.");
 	  		}
 	 	}
 	}  
restart_:
	restart();
	nemu_state = STOP;
	cmd_c();
}
static void cmd_si(const char* p){
	int m;
	if(p==NULL)
		m=1;
	else if(sscanf(p,"%d",&m)<=0){
		printf("the data is wrong!\n");
		return ;
	}
	if( nemu_state!=END){
		nemu_state=STOP;
	}
	else{
		restart();
		nemu_state=RUNNING;
		cpu_exec(m);
	} 
}
static void cmd_info(){
	printf("eax\t\t0x%x\n",cpu.eax);
	printf("ebx\t\t0x%x\n",cpu.ebx);
	printf("ecx\t\t0x%x\n",cpu.ecx);
	printf("edx\t\t0x%x\n",cpu.edx);
	printf("esp\t\t0x%x\n",cpu.esp);
	printf("ebp\t\t0x%x\n",cpu.ebp);
	printf("esi\t\t0x%x\n",cpu.esi);
	printf("edi\t\t0x%x\n",cpu.edi);
	printf("eip\t\t0x%x\n",cpu.eip);
}
static void cmd_x(char *p){
	int n,exp,i;
	if (p==NULL||sscanf(p,"%d",&n)<=0){
		printf("the data is wrong!\n");
		return ;
	}
	p=strtok(NULL," ");
	if(p==NULL||sscanf(p,"%x",&exp)<=0){
		printf("the data is wrong!\n");
		return ;
	}  
	for (i=0;i<n;i++){
		printf("0x%08x:\t\t%08x\n",exp+i*4,swaddr_read(exp+i*4,4));
	}
	for(i=0;i<n;i++){
		printf("0x%08x:%02x %02x %02x %02x\n",exp+i*4,swaddr_read(exp+i*4,1),swaddr_read(exp+i*4+1,1),swaddr_read(exp+i*4+2,1),swaddr_read(exp+i*4+3,1));
	}  
}
static void cmd_breakpoint(char* p){
	swaddr_t n;
	p=p+3;
	if(p==NULL||sscanf(p,"%x",&n)<=0){
		printf("the data is wrong!\n");
		return ;
	}  
	breakpoint_start(n);
}
static void cmd_watchpoint(char* p){
	swaddr_t n;
	p=p+3;
	if(p==NULL||sscanf(p,"%x",&n)<=0){
		printf("the data is wrong!\n");
		return ;
	}
	watchpoint_start(n);
}
static void cmd_expression(char* p){
	bool x[1];
	x[0]=true;
	printf("%d\n",expr(p,x));
}
static void cmd_d(){
	int n;
	printf("Delete how many breakpoints?");
	fflush(stdout);
	scanf("%d",&n);
	breakpoint_del(n);
}
static void cmd_bt(){
	int i=0;
	int j=0;
	Elf32_Sym* current=symtab;
	while(i<nr_symtab_entry){
		if(((current[i].st_info)&0x0000000f)==STT_FUNC){
			printf("#%d 0x%x %s\n",j,current[i].st_value,strtab+current[i].st_name);
			j++;
		}
		i++;
	}
}
	
void main_loop() {
	char *cmd;
	int d;
	while(1) { 
		cmd = rl_gets();
		char *p = strtok(cmd, " ");

		if(p == NULL) { continue; }

		if(strcmp(p, "c") == 0) { cmd_c(); }
		else if(strcmp(p, "r") == 0) { cmd_r(); }
		else if(strcmp(p, "q") == 0) {return; }
		else if(strcmp(p, "si")==0) {
			p=strtok(NULL," ");
			cmd_si(p);
	  	} 
		else if(strcmp(p, "info")==0){
			p=strtok(NULL," ");
			if(strcmp(p,"r")==0)
				cmd_info();
			else if(strcmp(p,"b")==0){
			   	printf("Num\tType\tDisp\tAddress\t\n");
				breakpoint_print();
		 	}
			else
				printf("Unknown Command!\n");
		} 
	  	else if(strcmp(p, "x")==0){
			p=strtok(NULL," ");
			cmd_x(p);
		} 
	 	else if(strcmp(p,"b")==0){
			p=strtok(NULL," ");
			cmd_breakpoint(p);
 		} 
 		else if(strcmp(p,"d")== 0){
			cmd_d();
		}
		else if(strcmp(p,"p")==0){
			p=p+2;
			cmd_expression(p);
 		}
        else if(strcmp(p,"watch")==0){
			bool y[1];
			y[0]=true;
			p=p+6;
			d=expr(p,y);
			sprintf(p,"%d",d);
			cmd_watchpoint(p);
		}
		else if(strcmp(p,"bt")==0){
			cmd_bt();
		}
		/* TODO: Add more commands */

		else { printf("Unknown command '%s'\n", p); }
 	} 
}
