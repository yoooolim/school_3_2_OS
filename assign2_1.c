/////////////////////////////////////////////////////////////////////// 
// File Name : Assignment2_1.c					     // 
// Date : 2020/05/08 		     			             // 
// Os : Ubuntu 12.04 LTS 64bits 				     //
// Author : Park Yoo LIm 					     //
// Student ID : 2017202010              			     //
// ----------------------------------------------------------------- //
// Title : System Programming Assignment #2-1 ( getopt() function )  //
// Description : Function for Parsing Program Execution OPtions	     //
///////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS    //strtok 보안 경고로 인한 컴파일 에러 방지

#include <unistd.h>
#include <stdio.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////
// main 							     // 
// ================================================================= // 
// Input: int argc -> argv's len				     // 
//        char ** argv -> parameter with command		     //
// Output: int 0 success 					     // 
//  							             // 
// (Out parameter Description)					     // 
// Purpose: Getopt() Run function and output result screen	     //
///////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
//////////////////////////////initialize//////////////////////////////
	int aflag = 0, bflag = 0;
	char *cvalue = NULL;
	int index, c;
	int i=0;
	opterr = 0;
//////////////////////////End of initialize//////////////////////////////


////////////////////read option & do option behavior//////////////
	while ((c = getopt(argc, argv, "abc:")) != -1) {
		switch (c) {
		case 'a':
			aflag = 1;
			break;
		case'b':
			bflag = 1;
			break;
		case 'c':
			if(strstr(argv[optind-1],"-c")!=NULL)
				cvalue=strtok(argv[optind-1],"-c");
			else	cvalue=argv[optind-1];
			break;
			
		}
	}
////////////////////End of read option & do option behavior//////////////


/////////////////////////print result//////////////////////
		printf("aflag = %d, bflag = %d, cvalue = %s\n", aflag, bflag, cvalue);
		for (index = optind; index < argc; index++)
			printf("Non-option argument %s\n", argv[index]);
		return 0;
/////////////////////////End of print result//////////////////////
}