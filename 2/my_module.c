#include <linux/module.h>
#include <linux/highmem.h>
#include <linux/kallsyms.h> /* kallsyms_lookup_name() */
#include <linux/syscalls.h> /* __SYSCALL DEFINEx() */
#include <asm/syscall_wrapper.h> /* __SYCALL_DEFINEx() */
#define __NR_add 349 //table number == 349

void **syscall_table; // system call table

void *real_add; //pointer that save original

__SYSCALL_DEFINEx(2, sub, int, a, int, b) // system call to wrapping -> substraction
{
	long result;
	result = a-b;
	return result; // return a-b
}

//A function that grants read and write access to the page with addr
void make_rw(void *addr)
{
	unsigned int level;
	pte_t *pte = lookup_address((u64)addr, &level);

	if(pte->pte &~ _PAGE_RW)
		pte->pte |= _PAGE_RW;
}

//Revoke read and write access to the page to which addr belongs
void make_ro(void *addr) 
{
	unsigned int level;
	pte_t *pte = lookup_address((u64)addr, &level); 

	pte->pte = pte->pte &~ _PAGE_RW; 
}

//Function called when loading module
static int __init hooking_init(void) { 

	//Function to find the address of the system call table
	syscall_table = (void**) kallsyms_lookup_name("sys_call_table"); 

	//Write permission to write-protected system call table
	make_rw(syscall_table); 

	//To restore the existing system call when the module is released, the existing system call address is saved.
	real_add = syscall_table[__NR_add]; 

	//The process of replacing the “sub” system call instead of the add system call
	syscall_table[__NR_add] = __x64_syssub;
   	printk(KERN_INFO "init_[2017202010]\n"); 
	return 0;
}

//Function called when module is released
static void __exit hooking_exit(void) { 
	//Restoring system calls
	syscall_table[__NR_add] = real_add; 

	make_ro(syscall_table); 
	printk(KERN_INFO "exit_[2017202010]\n"); 
}

module_init(hooking_init);
module_exit(hooking_exit);
MODULE_LICENSE("GPL");

