#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>

int main(int argc, char *argv[])
{
	int a=0,b=0; // input parameter
	long result; // result (output)

	if(argc != 3) { // if parameter is invalid -> error message
		printf("\n***** Not Valid Input Parameter *****\n\n");
	}
	else { // if parameter is valid
		a=atoi(argv[1]); 
		b=atoi(argv[2]); 
		result = syscall(349, a, b); // open 349 system call table -> add
   
		printf("%d + %d = %ld\n", a, b, result); 
	}

	return 0;
}

