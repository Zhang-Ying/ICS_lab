#include "../trap.h"

int test_data[]={3,60,-36,2,0,253,1,98};
int ans[]={9,180,-108,6,0,759,3,294,180,3600,-2160,120,0,15180,60,5880,-108,-2160,1296,-72,0,-9108,-36,-3528,6,120,-72,4,0,506,2,196,0,0,0,0,0,0,0,0,759,15180,-9108,506,0,64009,253,24794,3,60,-36,2,0,253,1,98,294,5880,-3528,196,0,24794,98,9604};
#define NR_DATA (sizeof(test_data)/sizeof(test_data[0]))

int multivate(int a,int b){
	int c;
	c=a*b;
	return c;
}
int main(){
	int i=0;
	int j=0;
	int ans_idx=0;
	for(i=0;i<NR_DATA;i++)
		for(j=0;j<NR_DATA;j++)
			nemu_assert(multivate(test_data[i],test_data[j])==ans[ans_idx++]);
	HIT_GOOD_TRAP;
	return 0;
}
