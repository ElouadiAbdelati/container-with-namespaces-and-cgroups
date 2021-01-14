#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <string.h>
#define STACK_SIZE (1024 * 1024)
static char stack[STACK_SIZE];

int child(void* arg)
{
  char c;
  //sethostname() sets the hostname to ELOUADI_KHADIM
  sethostname("ELOUADI_KHADIM",14);
  
  // changing the root directory of the child process to Host directory.
  chroot("./Host");
  
  //changing the current working directory of the child process to the root directory
  chdir("/");
  
  //Attaching the filesystem "proc " to "/proc" ,the third argument of mount refers to the type of the filesystem
  mount("proc", "/proc", "proc", 0, NULL);
  
  //this function execute the shell bash in the context of the child process
  execlp("/bin/bash", "/bin/bash" , NULL); 
  
  return 1;
}

int main()
{
    char bufMemory[255];
    char bufPid[255];
    /*
    in this case clone function will create a new isolate process that will execute child function:
    The stack argument specifies the location of the stack used by the child process. 
    CLONE_NEWNET  – isolate network devices
    CLONE_NEWUTS – host and domain names (UNIX Timesharing System)
    CLONE_NEWIPC – IPC objects
    CLONE_NEWPID – PIDs
    CLONE_NEWNS – mount points (file systems)
    CLONE_NEWUSER – users and groups
    SIGCHLD (anciennement SIGCLD) is a signal used to wake up a process where one of the children has just died
    */
    pid_t pid = clone(child, stack+STACK_SIZE,
    CLONE_NEWNET | CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWPID | CLONE_NEWNS | SIGCHLD, NULL);
      
    printf("child() in ns my PID: %d Parent ID=%d\n",pid,getpid());
    
    //cgcreate will create a new cgroup ELOUADI_KHADIM in memory controller with default values
    system("sudo cgcreate -g memory:ELOUADI_KHADIM");
   
   //Here we want to limit the memory that will be used by ELOUADI_KHADIM 
    system(" echo 20M > /sys/fs/cgroup/memory/ELOUADI_KHADIM/memory.limit_in_bytes");
   
    //Here we're gonna limit the swappiness
    system("sudo echo 0 > /sys/fs/cgroup/memory/ELOUADI_KHADIM/memory.swappiness");
    
    //We add the child process to the cgroup ELOUADI_KHADIM
    sprintf(bufMemory,"sudo echo %d  > /sys/fs/cgroup/memory/ELOUADI_KHADIM/cgroup.procs",pid);
    system(bufMemory);
    
    //cgcreate will create a new cgroup ELOUADI_KHADIM in PIDs controller with default values
    system("sudo cgcreate -g pids:ELOUADI_KHADIM");
   
    /* Here we want to limit the number of processes that can be launched from the shell bash 
    already executed in the context of isolated process  */
 
    system("echo 20 > /sys/fs/cgroup/pids/ELOUADI_KHADIM/pids.max");
    
    //finally we add the child process to the cgroup ELOUADI_KHADIM
    sprintf(bufPid,"sudo echo %d  > /sys/fs/cgroup/pids/ELOUADI_KHADIM/cgroup.procs",pid);
    system(bufPid);

    waitpid(pid, NULL, 0);
    return 0;
}

