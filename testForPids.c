#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

 

int main(int argc, char const *argv[])
{

    pid_t pid;
    
    for(int i=0;i<21;i++){
    pid=fork();
    if(pid > 0){
    printf("processus %d crée \n",i+1);
    sleep(5);
    }
    else if(pid ==-1){
    printf("processus %d non crée \n",i+1);
    }}
    return 0;

}
