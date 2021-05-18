#include <stdio.h>
#include <stdlib.h>
struct term{
    int at;
    int bt;
    int rt;
    int name;
    int wt;
    int tat;
};
typedef struct term sjterm;

void read_data(sjterm process[10], int n){
    int i = 0;
    for(i = 0; i<n; i++){
        printf("Enter Process Details P%d\n", i+1);
        process[i].name = i+1;
        printf("arrival time");
        scanf("%d",&process[i].at);
        printf("burst time");
        scanf("%d",&process[i].bt);
        process[i].wt = 0;
        process[i].tat = 0;
    }
}

void sort(sjterm process[10],int n){
    int i,j;
    sjterm t;
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if(process[i].at > process[j].at){
                t = process[i];
                process[i] = process[j];
                process[j] = t;
            }
        }
    }
}

void display(sjterm process[10], int n){
    int i;
    printf("\n\nPname   at  bt  wt  tat\n");
    for(i=0;i<n;i++){
        printf("\n\tP%d\t%d\t%d\t%d\t%d\n",process[i].name,process[i].at,process[i].bt,process[i].wt,process[i].tat);

    }
}

void sjfpm(sjterm process[10], int n){
    int i,j,min,curr_time,min_index;
    float av_wt,av_tat;
    curr_time = process[0].at;
    printf("\n\n        Gantt Chart     \n");
    printf("%d",curr_time);
    while(1){
        min = 999;
        min_index= -1;
        i=0;
        while(i<n && process[i].at <= curr_time){
            if(process[i].rt!=0 && process[i].rt < min){
                min = process[i].rt;
                min_index=i;
            }
            i++;
        }
        if(i==n && min_index == -1){
            break;
        } else if(i!=n && min_index ==-1){
            printf("<-IDLE->");
            curr_time=process[i].at;
        } else if(i==n && min_index!=-1){
            j=min_index;
            printf("<--P%d-->",process[j].name);
            curr_time += process[j].rt;
            process[j].rt = 0;
            process[j].tat = curr_time-process[j].at;
            process[j].wt = process[j].tat - process[j].bt;
        } else{
            j=min_index;
            printf("<--P%d-->",process[j].name);
            curr_time ++;
            process[j].rt --;
            if(process[j].rt==0){
                process[j].tat = curr_time-process[j].at;
                process[j].wt = process[j].tat - process[j].bt;
            }
        }
        printf("%d",curr_time);
        // av_wt=(float)tot_wt/n;
        // av_tat=(float)tot_tat/n;
        // printf("\nAverage waiting time is:%f\n",av_wt);
        // printf("\nAverage turn around  time is:%f\n",av_tat);
    }
}


int main(){
    sjterm process[10];
    int n;
    printf("Enter the number of process\n");
    scanf("%d",&n);
    read_data(process,n);
    sort(process,n);
    printf("Before processing\n");
    display(process,n);
    sjfpm(process,n);
    printf("After processing");
    display(process,n);
}
