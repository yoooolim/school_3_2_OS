#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define MAX_PROCESSES 102 // number of max process = Even number of 2 or more
//#define BuffSize (int)(pow(19.0,(double)MAX_PROCESSES))
int temp[MAX_PROCESSES*2]; //thread return array

void * multiplier(int num){//multiplication function
    pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
    FILE* fd = NULL;
    fd = fopen( "temp.txt", "a+" ); // open
    char Buff[100];
    memset(Buff,0,sizeof(Buff));
    //char * Buff = (char*)malloc(sizeof(char)*BuffSize);
    unsigned long long result=0;

    pthread_mutex_lock(&counter_mutex); // lock
    
    if(fd!=NULL){
        memset(Buff,0,sizeof(Buff));
        int line_counter=0;
        unsigned long long a=0,b=0;

        while(fgets(Buff,sizeof(Buff),fd)!=NULL){
            if(line_counter==num*2){
                a=atoll(Buff);
                memset(Buff,0,sizeof(Buff));
                if(a==0||fgets(Buff,sizeof(Buff),fd)==NULL) {
                    fclose(fd);
                    pthread_mutex_unlock(&counter_mutex);
                    //free(Buff);
                    return ;
                }
                b=atoll(Buff);
                if(b==0){
                    fclose(fd);
                    fd = fopen( "temp.txt", "a+" ); // re open
                    for(int i=0;i<line_counter;i++) fgets(Buff,sizeof(Buff),fd);
                    memset(Buff,0,sizeof(Buff));
                    if(fgets(Buff,sizeof(Buff),fd)!=NULL) b=atoll(Buff);
                }
                //printf("%lld %lld \n",a,b);
                break;
            }
            memset(Buff,0,sizeof(Buff));
            line_counter++;
        }
        result = a * b ;
    }
    //printf("%llu\n",result);
    fprintf(fd,"%llu\n",result);
    memset(Buff,0,sizeof(Buff));
    pthread_mutex_unlock(&counter_mutex);
    fclose(fd);
    //free(Buff);
}


int main(){
    struct timespec S={0,0}, E={0,0};
    int processN = MAX_PROCESSES;
    int loop_count=0;
    clock_gettime(CLOCK_MONOTONIC, &S); // start time
    while(processN>0){
        pthread_t tid[processN];
        for(int i=0; i<processN; i++){ 
            //sleep(0.00001);
            int * temp = pthread_create(&tid[i],NULL,(void*)multiplier,loop_count+i); // create
        }
        for(int i=0; i<processN; i++){ 
            int val=pthread_join(tid[i],(void**)&temp[i]);//join
        }
        loop_count+=processN;
        processN/=2;//next depth
    }
    clock_gettime(CLOCK_MONOTONIC, &E); // end
    printf("Run time : %.6f\n",((double)E.tv_sec + 1.0e-9*E.tv_nsec)-((double)S.tv_sec + 1.0e-9*S.tv_nsec)); //calculate
    return 0;
}

