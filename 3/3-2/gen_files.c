#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_PROCESSES 10000

int main(){
	mkdir("tem",0777);//make directory named tem => 0777 => all authority
    chdir("tem"); //go to tem

	for(int i=0; i<MAX_PROCESSES; i++){
        char filename[20];
        sprintf(filename,"%d",i);//set name of file

        FILE* fd = fopen(filename,"w");//open
		fprintf(fd,"%d\n",1+rand()%9);//generate random number
        fclose(fd);//close
	}
	return 0;
}

