#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(rep_movs_,SUFFIX)){
	int count=REG(1);
	int src=REG(6);
	int i;
	for(i=0;i<count;i++){
		MEM_W(REG(7),MEM_R(src));
		src+=4;
		REG(7)+=4;
	}
	print_asm("rep movs");
	return 2;
}

#include "exec/template-end.h"
