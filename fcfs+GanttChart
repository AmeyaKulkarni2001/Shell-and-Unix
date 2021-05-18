#include<stdio.h>
#include<stdlib.h>

struct s{
    int at;
    int bt;
    int name;
    int wt;
    int tat;
};

typedef struct s node;

void read_data(node p[10],int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("\n\nEnter details for process P%d\n\n",i+1);
        p[i].name=i+1;
        printf("Enter arrival time:");
        scanf("%d",&p[i].at);
        printf("Enter burst time:");
        scanf("%d",&p[i].bt);
        p[i].wt=0;
        p[i].tat=0;
        
    }
}

void display(node p[10],int n)
{
    int i;
    printf("\n\n\n\tPname\tat\tbt\twat\ttat\n");
    for(i=0;i<n;i++)
    {
        printf("\n\tP%d\t%d\t%d\t%d\t%d\t\n",p[i].name,p[i].at,p[i].bt,p[i].wt,p[i].tat);
    }
}

void sort(node p[10],int n)
{
    int i,j;
    node temp;
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(p[i].at>p[j].at)
            {
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
}

void fcfs(node p[10],int n)
{
    int i,curr_time,tot_wt,tot_tat;
    float av_wt,av_tat;
    tot_wt=0;
    tot_tat=0;
    curr_time=p[0].at;
    printf("\n\nGANTT CHART\n\n");
    printf("%d",curr_time);
    for(i=0;i<n;i++)
    {
        printf("<--P%d-->",p[i].name);
        curr_time=curr_time+p[i].bt;
        p[i].tat=curr_time-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
        tot_wt=tot_wt+p[i].wt;
        tot_tat=tot_tat+p[i].tat;
        printf("%d",curr_time);
        if(i<n-1&&curr_time<p[i+1].at)
        {
            printf("<-IDLE->");
            curr_time=p[i+1].at;
            printf("%d",curr_time);
            
        }
    }
    printf("\n");
    display(p,n);
    av_wt=(float)tot_wt/n;
    av_tat=(float)tot_tat/n;
    printf("\nAverage waiting time is:%f\n",av_wt);
    printf("\nAverage turn around  time is:%f\n",av_tat);
    
}

int main()
{
    node process[10];
    int n;
    printf("Enter no. of processes:");
    scanf("%d",&n);
    read_data(process,n);
    display(process,n);
    sort(process,n);
    printf("\nAfter sorting:\n");
    display(process,n);
    fcfs(process,n);
    return 0;
}
