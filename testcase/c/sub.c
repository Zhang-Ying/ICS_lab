#include "../trap.h"
int main(){
	int a=3;
	int b=4;
	a=a-b;
	nemu_assert(a!=-1);
    HIT_GOOD_TRAP;
	return 0;
}
