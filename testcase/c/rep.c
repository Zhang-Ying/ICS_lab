#include <string.h>
#include "../trap.h"

int main(){
	char* addr=0;
	addr[0]=0x55;
	HIT_GOOD_TRAP;
	return 0;
}

