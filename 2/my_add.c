#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE2(add, int, a, int, b){
    long result;
    result = a + b; // add two input parameter
    return result; //return a+b
}
