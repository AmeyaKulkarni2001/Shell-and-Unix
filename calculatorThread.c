#include <stdio.h>
#include <pthread.h>

int add1(int a[3])
{
    a[2]=a[0]+a[1];
    printf("\nAddition thread result: %d",a[2]);
}

int sub1(int a[3])
{
    a[2]=a[0]-a[1];
    printf("\nSubtraction thread result: %d",a[2]);
}

int mul1(int a[3])
{
    a[2]=a[0]*a[1];
    printf("\nMultiplication thread result: %d",a[2]);
}
int div1(int a[3])
{
    a[2]=a[0]/a[1];
    printf("\nDivision thread result: %d",a[2]);
}

int main()
{
    int a[3],i;
    pthread_t thread1,thread2,thread3,thread4;
    
    printf("\nEnter numbers: ");
    scanf("%d%d",&a[0],&a[1]);

    
    pthread_create(&thread1,NULL,(void*)add1,a);
    pthread_create(&thread2,NULL,(void*)sub1,a);
    pthread_create(&thread3,NULL,(void*)mul1,a);
    pthread_create(&thread4,NULL,(void*)div1,a);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);
    pthread_join(thread4,NULL);

    return 0;
}
