#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void input(int *a, int n) 
{
    for(int i=0; i<n; i++)
    {
        printf("Enter value of element #%d :- ", i+1);
        scanf("%d", &a[i]);
    }
}

void display(int *a, int n) 
{
    for(int i=0; i<n; i++) 
    {
        printf("%d ", a[i]);
    }
}

void sort(int *a, int n, int c)      
{
    for(int i=0; i<n; i++) 
    {
        for(int j=0; j<n-1; j++) 
        {
            if( a[j] > a[j+1] && c == 1)
            {
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            } 
            else if ( a[j] < a[j+1] && c == 0) 
            {
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}
pid_t num_pid;

int main()
{
    int n;
    printf("Enter the number of elements :- ");
    scanf("%d", &n);
    int a[n];
    input(a, n);
    printf("\nThe array to be sorted is :- ");
    display(a, n);
    printf("\n");
    num_pid = fork();            
    if (num_pid == 0)
    {
        printf("\nChild Process id is %d\n",getpid());
        sort(a, n, 0);          
        printf("The sorted array in decending order is:-");
        display(a, n);
        exit(1);            // with status 1
    } 
    else 
    {
        sort(a, n, 1); 
        printf("\nParent Process id is %d\n",getpid());
        printf("The sorted array in ascending order is:- ");
        display(a, n);
    }
    printf("\n");
    return 0;
}
