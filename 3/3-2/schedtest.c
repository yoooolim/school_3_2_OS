#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>

#define MAX_PROCESSES 10000 // Max_Proccesses

int menuNum=-1;
void printMenu();//function
//void threadAction();

int main(){
    struct timespec S={0,0}, E={0,0};//start, end time set
    int processN=MAX_PROCESSES;
    double record = 0.0;
    struct sched_param p; //sched parameter
    int status;

    printMenu();
    scanf("%d",&menuNum);
    if(menuNum<0||menuNum>8){//over menu number
        printf("Not that number in menu\n");
        return -1;
    }
    
        clock_gettime(CLOCK_MONOTONIC, &S);//start time
        for(int j=0;j<processN;j++){
            pid_t pid;
            pid=fork();
            if(pid<0){
                printf("fork error\n");
                return -1;
            }
            else if(pid>0){continue;}
            else{
                switch (menuNum){
                    case 0: //RR_time-sharing(h)
                        p.sched_priority=0;
                        nice(-20);
                        if(sched_setscheduler(getpid(), SCHED_OTHER, &p) == -1) return -10;
                        break;

                    case 1: //RR_time-sharing(d) 
                        p.sched_priority=0;
                        nice(0);
                        if(sched_setscheduler(getpid(), SCHED_OTHER, &p) == -1) return -11;
                        break;

                    case 2: //RR_time-sharing(l)
                        p.sched_priority=0;
                        nice(19);
                        if(sched_setscheduler(getpid(), SCHED_OTHER, &p) == -1) return -12;
                        break;

                    case 3: //FIFO(h)
                        p.sched_priority=sched_get_priority_min(SCHED_FIFO);
                        if(sched_setscheduler(getpid(), SCHED_FIFO, &p) == -1) return -13;
                        break;
            
                    case 4: //FIFO(d) 
                        p.sched_priority=50;
                        if(sched_setscheduler(getpid(), SCHED_FIFO, &p) == -1) return -14;
                        break;
            
                    case 5: //FIFO(l)
                        p.sched_priority=sched_get_priority_max(SCHED_FIFO);
                        if(sched_setscheduler(getpid(), SCHED_FIFO, &p) == -1) return -15;
                        break;
            
                    case 6: //RR(h)
                        p.sched_priority=sched_get_priority_min(SCHED_RR);
                        if(sched_setscheduler(getpid(), SCHED_RR, &p) == -1) return -16;
                        break;
            
            
                    case 7: //RR(d)
                        p.sched_priority=50;
                        if(sched_setscheduler(getpid(), SCHED_RR, &p) == -1) return -17;
                        break;
            
            
                    case 8: //RR(l)
                        p.sched_priority=sched_get_priority_max(SCHED_RR);
                        if(sched_setscheduler(getpid(), SCHED_RR, &p) == -1) return -18;
                        break;
            
                    default:
                        break;
                }
                chdir("tem"); //go to tem directory
                char filename[10];
                memset(filename,0,sizeof(filename));
                char Buff[100];
                memset(Buff,0,sizeof(Buff));
                char * ptr=NULL;
                sprintf(filename,"%d",j); //setting file name

                FILE * fd = NULL; //file
                fd = fopen(filename,"r");//open
                if(fd!=NULL){
                    ptr = fgets(Buff,sizeof(Buff),fd); //read line
                    fclose(fd); //close
                }
                exit(0);
            }
        }
        for(int i=0; i<processN; i++){
            wait(&status); // wait
        }
        clock_gettime(CLOCK_MONOTONIC, &E);
        record=((double)E.tv_sec + 1.0e-9*E.tv_nsec)-((double)S.tv_sec + 1.0e-9*S.tv_nsec); //calculate
    printf("\n\n<Result>\n%f\n",record);
}

void printMenu(){//menu setting
    printf("\n<Select CPU Scheduling policy>\n\n(h):highest / (d):default / (l):lowest\n");
    printf("=============================================================================\n");
    printf("0. RR_time-sharing(h)   / 1. RR_time-sharing(d)     / 2. RR_time-sharing(l)\n");
    printf("3. FIFO(h)              / 4. FIFO(d)                / 5. FIFO(l)\n");
    printf("6. RR(h)                / 7. RR(d)                  / 8. RR(l)\n");
    printf("=============================================================================\n");
    printf("what is your selection => ");

}

/*
void childAction(){
    struct sched_param p;    
    for(int i=0; i<MAX_PROCESSES; i++){
        switch(menuNum){
            case 0: //RR_time-sharing(h)
                p.sched_priority=0;
                nice(-20);
                if(sched_setscheduler())
            case 1: //RR_time-sharing(d) 

            case 2: //RR_time-sharing(l)
            
            case 3: //FIFO(h)
            
            case 4: //FIFO(d) 
            
            case 5: //FIFO(l)
            
            case 6: //RR(h)
            
            case 7: //RR(d)
            
            case 8: //RR(l)

        }

    }
}*/
