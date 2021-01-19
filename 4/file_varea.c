            #include <linux/module.h>
            #include <linux/highmem.h>
            #include <linux/kallsyms.h> /* kallsyms_lookup_name() */
            #include <linux/syscalls.h> /* __SYSCALL DEFINEx() */
            #include <asm/syscall_wrapper.h> /* __SYCALL_DEFINEx() */
            #include <linux/sched/mm.h>

            #define __NR_add 349 //table number == 349

            void **syscall_table; // system call table

            void *real_add; //original

            __SYSCALL_DEFINEx(1,info,pid_t,pid) // system call to wrapping -> substraction
            {
                struct task_struct *tStruct;
                struct mm_struct *mStruct;
                struct vm_area_struct *vaStruct; //Start address of vm_area_struct list

                tStruct = pid_task(find_vpid(pid),PIDTYPE_PID);
                mStruct = get_task_mm(tStruct);
                printk(KERN_INFO "########## Loaded files of a process 'test(%d)' in VM ##########\n",pid);
                vaStruct=mStruct->mmap; // get vaStruct 1 page of vm area struct
                while(vaStruct->vm_next!=NULL){
                    char * directory;
                    char buff[256];
                    memset(buff,NULL,256);
                    if(vaStruct->vm_file != NULL){
                        directory = dentry_path_raw(vaStruct->vm_file->f_path.dentry,buff,255);
                        printk(KERN_INFO "mem(%lx~%lx) code(%lx~%lx) data(%lx~%lx) heap(%lx~%lx)  %s\n" ,vaStruct->vm_start,vaStruct->vm_end,
                        mStruct->start_code,mStruct->end_code,mStruct->start_data,mStruct->end_data,mStruct->start_brk,mStruct->brk,directory);
                    
                        /*printk(KERN_INFO "name[%s]  mem(%lx~%lx) code(%lx~%lx) data(%lx~%lx) heap(%lx~%lx)  %s\n"
                        ,tStruct->comm,vaStruct->vm_start,vaStruct->vm_end,mStruct->start_code,mStruct->end_code
                        ,mStruct->start_data,mStruct->end_data,mStruct->start_brk,mStruct->brk,directory);
                    */
                    }
                
                    vaStruct=vaStruct->vm_next;
                }//printk(KERN_INFO "name[%s]  code[%lx~%lx]\n",tStruct->comm,mStruct->start_code,mStruct->end_code);
                printk(KERN_INFO "#################################################################\n");
                mmput(mStruct);
            }

            void make_rw(void *addr) // read and write permissions function
            {
                unsigned int level;
                pte_t *pte = lookup_address((u64)addr, &level);
                if(pte->pte &~ _PAGE_RW)
                    pte->pte |= _PAGE_RW;
            }

            void make_ro(void *addr) // read and write permission function
            {
                unsigned int level;
                pte_t *pte = lookup_address((u64)addr, &level); 
                pte->pte = pte->pte &~ _PAGE_RW; //get back permission
            }

            static int __init hooking_init(void) {  // when moudle in
                syscall_table = (void**) kallsyms_lookup_name("sys_call_table"); 
                make_rw(syscall_table); 
                real_add = syscall_table[__NR_add]; 
                syscall_table[__NR_add] = __x64_sysinfo;
                printk(KERN_INFO "init_[2017202010]\n"); 
                return 0;
            }

            static void __exit hooking_exit(void) { //when module out
                syscall_table[__NR_add] = real_add;
                make_ro(syscall_table); 
                printk(KERN_INFO "exit_[2017202010]\n"); 
            }

            module_init(hooking_init);
            module_exit(hooking_exit);
            MODULE_LICENSE("GPL");

