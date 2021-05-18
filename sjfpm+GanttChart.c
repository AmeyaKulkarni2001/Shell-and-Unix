#include<stdio.h>
#include<stdlib.h>

struct term{
    int at;
    int bt;
    int rt;
    int name;
    int wt;
    int tat;
};
typedef struct term sjterm;

void read_data(sjterm p[10],int n)
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
        p[i].rt=p[i].bt;
        p[i].wt=0;
        p[i].tat=0;
        
    }
}

void display(sjterm p[10],int n)
{
    int i;
    printf("\n\n\n\tPname\tat\tbt\twat\ttat\n");
    for(i=0;i<n;i++)
    {
        printf("\n\tP%d\t%d\t%d\t%d\t%d\t\n",p[i].name,p[i].at,p[i].bt,p[i].wt,p[i].tat);
    }
}

void sort(sjterm p[10],int n)
{
    int i,j;
    sjterm temp;
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


void sjfpm(sjterm p[10],int n)
{
    int i,j,min,curr_time,min_index,tot_wt,tot_tat;
    float av_wt,av_tat;
    curr_time=p[0].at;
    printf("\n\n\tGANT CHART\t\n\n");
    printf("%d",curr_time);
    while(1)
    {
        min=999;
        min_index=-1;
        i=0;
        while(i<n&&p[i].at<=curr_time)
        {
            if(p[i].rt!=0&&p[i].rt<min)
            {
                min=p[i].rt;
                min_index=i;
            }
            i++;
        }
        if(i==n&&min_index==-1)
        {
            break;
        }
        else if(i!=n&&min_index==-1)
        {
            printf("<-IDLE->");
            curr_time=p[i].at;
        }
        else if(i==n&&min_index!=-1)
        {
            j=min_index;
            printf("<--P%d-->",p[j].name);
            curr_time=curr_time+p[j].rt;
            p[j].rt=0;
            p[j].tat=curr_time-p[j].at;
            p[j].wt=p[j].tat-p[j].bt;
            tot_tat += p[j].tat;
            tot_wt += p[j].wt;
            
        }
        else
        {
            j=min_index;
            printf("<--P%d-->",p[j].name);
            curr_time=curr_time+1;
            p[j].rt=p[j].rt-1;
            if(p[j].rt==0)
            {
                p[j].tat=curr_time-p[j].at;
                p[j].wt=p[j].tat-p[j].bt;
                tot_tat += p[j].tat;
                tot_wt += p[j].wt;
            }
        }
        printf("%d",curr_time);
    }
    printf("\n");
    av_wt=(float)tot_wt/n;
    av_tat=(float)tot_tat/n;
    printf("\nThe average waiting time is: %f",av_wt);
    printf("\nThe average turaround time is: %f",av_tat);
}


int main()
{
    sjterm process[10];
    int n;
    printf("Enter no. of processes:");
    scanf("%d",&n);
    read_data(process,n);
    sort(process,n);
    printf("\n Before processing sorted on arrival time \n");
    display(process,n);
    sjfpm(process,n);
    printf("\n After processing \n");
    display(process,n);
    
    return 0;
}
