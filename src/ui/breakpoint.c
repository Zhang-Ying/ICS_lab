#include "ui/breakpoint.h"
#include<stdlib.h>
#include "nemu.h"
#define NR_BP 32
void breakpoint_continue(swaddr_t n);
void watchpoint_continue(swaddr_t n);
void main_loop();
static BP bp_pool[NR_BP];
static BP *head, *free_;
void init_bp_pool() {
	int i;
	for(i = 0;  i <  NR_BP - 1; i ++) {
		bp_pool[i].NO = i;
		bp_pool[i].next = &bp_pool[i + 1];
 	}
	head = NULL;
	free_ = bp_pool;
}
void new_bp(){
	BP* current=head;
	if(free_==NULL)
		assert(0);
	if(head==NULL){
		head=&bp_pool[0];
		head->next=NULL;
		free_=&bp_pool[1];
	}
    else{
		while(current->next!=NULL)
			current=current->next;
		current->next=free_;
		free_=free_->next;
		current->next->next=NULL;
	}
}
void free_bp(int n){
    BP*	temp=head;
	BP *p;
	while(temp->NO!=n&&temp->next!=NULL)
		temp=temp->next;
	if(temp->NO!=n)
		printf("The data is wrong!\n");
	else if(temp==head){
		p=head;
		head=head->next;
		p->next=free_;
		free_=p;
	}
	else{
		p=temp;
		p->next=free_;
		free_=p;
		p->next=NULL;
	}
}	
void breakpoint_start(swaddr_t n){
	int m;
	BP *temp;
	BP* p;
	m=swaddr_read(n,1);
	new_bp();
	temp=head;
	p=head;
	assert(head!=NULL);
	while(temp->next!=NULL)
		temp=temp->next;
    temp->instr=m;
	temp->address=n;
	temp->type=true;
	head=p;
	breakpoint_continue(n);
}
void breakpoint_continue(swaddr_t n){
    printf("set breakpoint successfully!\n");
}
void watchpoint_start(swaddr_t n){
	int m;
	BP* temp;
	BP* p;
	m=swaddr_read(n,1);
	new_bp();
	temp=head;
	p=head;
	assert(head!=NULL);
	while(temp->next!=NULL)
		temp=temp->next;
	temp->instr=m;
	temp->address=n;
	temp->type=false;
	head=p;
	watchpoint_continue(n);
}
void watchpoint_continue(swaddr_t n){
	printf("set watchpoint successfully!\n");
}
void breakpoint_print(){
	BP* temp=head;
	int Num;
	swaddr_t n;
	while(temp!=NULL){
			Num=temp->NO;
			n=temp->address;
			printf("%d\t",Num+1);
			if(temp->type==true)
				printf("breakpoint\tkeep\t");
			else 
				printf("watchpoint\tkeep\t");
			printf("%x\t\n",n);
			temp=temp->next;
	}  
}
void breakpoint_del(int n){
	free_bp(n-1);
}
void breakpoint_reset(swaddr_t n){
	BP* temp=head;
	while(temp->next!=NULL&&temp->address!=n)
		temp=temp->next;
	swaddr_write(n,1,temp->instr);
}
void breakpoint_preset(){
    BP* temp=head;
	if(head==NULL)
		return;
	if(head->type==true){
		while(temp!=NULL){
			swaddr_write(temp->address,1,0xcc);
			temp=temp->next;
		}
	}
	else{
		while(temp!=NULL){
			if(swaddr_read(temp->address,4)!=temp->instr)
				swaddr_write(temp->address,1,0xcc);
			temp=temp->next;
		}
	}
}


/* TODO: Implement the function of breakpoint */
