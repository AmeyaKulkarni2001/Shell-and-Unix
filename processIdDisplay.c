#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>



pid_t num_pid;

int main()
{
    num_pid=fork();
    if(num_pid==0)
    {
        printf("This is the child process id %d\n",getpid());
        
    } if(num_pid>0) {
        
        printf("This is the parent process id %d\n",getpid());
    }
    return 0;
    
}
