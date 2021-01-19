#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 102 // number of max process = Even number of 2 or more

int main()
{
	FILE* fd = fopen("temp.txt","w"); //open

	for(int i=0; i<MAX_PROCESSES*2; i++)
	{
		fprintf(fd,"%d\n",2+rand()%20); // MAX number == 21 & MIN number ==
	}

	fclose(fd);//close
	return 0;
}

