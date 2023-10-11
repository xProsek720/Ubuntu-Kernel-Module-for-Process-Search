#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
static char *process_name = "cs2";

static int __init my_module_init(void) {
    struct task_struct *task;
    pid_t pid = -1;

    rcu_read_lock();
    for_each_process(task) {
        if (strcmp(task->comm, process_name) == 0) {
            pid = task->pid;
            break;
        }
    }
    rcu_read_unlock();

    if(pid != -1) {
        printk(KERN_INFO "Found %s with PID: %d\n", process_name, pid);


    } else {
        printk(KERN_INFO "Process %s not found\n", process_name);
    }
    return 0;
}

static void __exit my_module_exit(void) {
    printk(KERN_INFO "Module Unloaded\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Find Process by Name Kernel Module");

