#include "../trap.h"
#include <string.h>

int main(){
	char* addr=(char*)0x800;
	addr[0]=0x55;
	HIT_GOOD_TRAP;
	return 0;
}
