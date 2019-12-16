#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    char *a = (char *)main;
	
	if (fork() == 0) {
		printf(1,"[CHILD] main addr before: %x\n", *a);
		*a = 0;
		printf(1,"[CHILD] main addr after: %x\n", *a);
		exit();
	}
	
	wait();	
	printf(1,"[PARENT] main addr before: %x\n", *a);
	*a = 0;
	printf(1,"[PARENT] main addr after: %x\n", *a);
	
    exit();
}
