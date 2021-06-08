#include<stdio.h>
struct term
{
 int f_no,count;
 char bit;
};
typedef struct term pterm;
void display_buffer(int buffer[10],int no_of_frames)
{
 int k;
 for(k=0;k<no_of_frames;k++)
 {
if(buffer[k]!=-1)
 printf(" %d |",buffer[k]);
else
 printf(" - |");
}
}
void init(int buffer[10],pterm pg_table[10],int no_of_frames)
{
 int i;
 for(i=0;i<no_of_frames;i++)
 buffer[i]=-1;
 for(i=0;i<10;i++)
 pg_table[i].bit='I'; //set invalid for all pages//
}
void fifo(int refstr[20],int n,int no_of_frames)
{
 pterm pg_table[10];
 int i,j=0,k,p,pg_no,front=0,buffer[10],page_faults=0;
 init(buffer,pg_table,no_of_frames);
 printf("\n Page Replacement Using FIFO :-\n");
 for(i=0;i<n;i++)
{
 pg_no=refstr[i];
 printf("\n For Page no. %d : |",pg_no);
 if(pg_table[pg_no].bit=='I') //page fault//
 {
 if(j<no_of_frames) //page fault but free frame available//
 {
buffer[j]=pg_no;
j++;
 }
 else //page replacement//
 {
 p=buffer[front];
 pg_table[p].bit='I';
 buffer[front]=pg_no;
 front=(front+1)%no_of_frames;
 }
 pg_table[pg_no].bit='V';
 page_faults++;
 display_buffer(buffer,no_of_frames);
 printf(" (M)");
 } //end of page fault//
 else
 {
 display_buffer(buffer,no_of_frames);
 printf(" (H)");
 }
 } //end of for//
 printf("\n Total page faults = %d",page_faults);
}
void lru(int refstr[20],int n,int no_of_frames)
{
 pterm pg_table[10];
 int
i,j=0,k,p,r,m,found,min,pg_no,front,buffer[10],page_faults=0;
 init(buffer,pg_table,no_of_frames);
 printf("\n\n Page Replacement Using LRU :-\n");
 for(i=0;i<n;i++)
 {
 pg_no=refstr[i];
 pg_table[pg_no].count=i;
 printf("\n For Page no. %d : |",pg_no);
 if(pg_table[pg_no].bit=='I') //page fault//
 {
 if(j<no_of_frames) //page fault but free frame available//
{
buffer[j]=pg_no;
j++;
}
 else //page replacement//
 {
//r will be index into buffer & buffer[r] will be page replaced//
 min=99;
 for(k=0;k<no_of_frames;k++)
 {
 p=buffer[k];
 if(pg_table[p].count<min)
 {
min=pg_table[p].count;
r=k;
 }
 }
 p=buffer[r];
 buffer[r]=pg_no;
 pg_table[p].bit='I';
 } //end of page replacement//
 pg_table[pg_no].bit='V';
 page_faults++;
 display_buffer(buffer,no_of_frames);
 printf(" (M)");
 } //end of page fault//
 else
 {
 display_buffer(buffer,no_of_frames);
 printf(" (H)");
 }
 } //end of for//
 printf("\n Total page faults = %d",page_faults);
}
int main()
{
int refstr[25],i,n,no_of_frames,num;

printf(" Enter the length of ref. string = ");
scanf("%d",&n);
printf(" Enter no. of frames = ");
scanf("%d",&no_of_frames);
printf(" Enter reference string :-\n");
for(i=0;i<n;i++)
 {
 printf(" Refstr[%d] = ",i);
 scanf("%d",&refstr[i]);
 }

 do{
    printf("\n1) fifo\n2) lru\n3) exit");
    scanf("%d",&num);
    switch(num){
        case 1: fifo(refstr,n,no_of_frames);
        break;
        case 2: lru(refstr,n,no_of_frames);
        break;
        case 3: break;
        default: printf("Wrong choice");
    }
     
 }while(num != 3);

return 0;
}
