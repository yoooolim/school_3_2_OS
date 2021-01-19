#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#define __NR_add 349

int main(){
    int a,b;
    a=7;
    b=4;
    #ifdef WRAPPING
        printf("%d add %d = %ld\n",a,b,syscall(__NR_add,getpid()));
    #else
        printf("%d add %d = %ld\n",a,b,syscall(__NR_add,a,b));
    #endif
    return 0;
}
