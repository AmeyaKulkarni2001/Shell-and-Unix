#include <stdio.h>
#include <stdlib.h>

struct process 
{		
	int p_no;		
	int arrival_time; 	
	int burst_time;	
	int turnaround_time;	
	int wait_time;		
};

int input(); 							
void processInfo(struct process*, int); 
void FCFS(struct process*, int); 		
void SJF(struct process*, int);			

int main() 
{

	int no = input();
	struct process p[no];
	int choice = 10;
	while (choice != 0) {
		printf("\nPlease enter your choice:\n1. First Come First Serve Algorithm\n2. Shortest Job First (pre-emptive)\n3. Exit\n");
		scanf("%d", &choice);
		switch(choice) {
			case 1:
				processInfo(p, no);
				FCFS(p, no);
				break;
			case 2: 
				processInfo(p, no);
				SJF(p, no);
				break;
			case 3:
				printf("\nEnd Of Program\n");
				choice = 0;
				break;
			default: 
				printf("%s\n", " Wrong Choice ");
				break;
		}
	}
	return 0;
}

int input() {
	int a;
	printf("\nPlease enter the number of process :- \t");		
	scanf("%d", &a);
	return a;
}

void processInfo(struct process *p, int lim) 
{
	for (int i=0; i<lim; i++) 
	{				
		printf("\nProcess %d\n", i+1);
		printf("Enter arrival time :- \t");
		scanf("%d", &p[i].arrival_time);
		printf("Enter burst time :- \t");
		scanf("%d", &p[i].burst_time);
		p[i].p_no = i+1;
	}
	struct process temp;
	for(int i=0; i<lim-1; i++) 
	{		
		for(int j=0; j<lim-1-i; j++) {			
			if(p[j].arrival_time > p[j+1].arrival_time) {
				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;		
			}
		}
	}
}

void FCFS(struct process *p, int n) {
	int total_wt = 0;	
	int total_tat = 0;	

	int current_time = p[0].arrival_time; 

	printf("\nGantt Chart:\n");
	printf("%d", current_time);
	//for each process calculate the turnaround time and waiting time and display it in the form of gantt chart
	for(int i=0; i<n; i++) {	
		current_time += p[i].burst_time;
		printf(" <---P%d---> %d", p[i].p_no, current_time);
		p[i].turnaround_time = current_time - p[i].arrival_time;
		p[i].wait_time = p[i].turnaround_time - p[i].burst_time;
		total_tat += p[i].turnaround_time;
		total_wt += p[i].wait_time;
		if(i < n-1 && current_time < p[i+1].arrival_time)
		{	 
			current_time = p[i+1].arrival_time;
			printf(" <---IDLE---> %d", current_time);
		}
	}

	
	printf("\n\nProcess\tArrival\tBurst\tTurnaround\tWait\n");
	printf("\tTime\tTime\tTime\t\tTime\n");
	for(int i=0; i<n; i++) 
	{
		printf("P%d\t%d\t%d\t%d\t\t%d\n", p[i].p_no, p[i].arrival_time, p[i].burst_time, p[i].turnaround_time, p[i].wait_time);
	}
	float avg_tat=(float)total_tat/n;
	float avg_wt=(float)total_wt/n;
	printf("\nTotal Turn around time = %d\n",total_tat);
	printf("\nAverage Turn around time = %.2f\n",avg_tat);
	printf("\nTotal Waiting time = %d\n",total_wt);
	printf("\nAverage Waiting time = %.2f\n",avg_wt);
}

void SJF(struct process *p, int n) 
{
	int remaining_time[n];	// burst time remaining
	int total_wt = 0;		
	int total_tat = 0;		

	int current_time = p[0].arrival_time;
	int cnt = 0;		 // processes parsed
	int least_rt = 9999; // least remaining time
	int k;				 // least index

	int i=0; // counter
	//storing the burst time in a separate array of remaining time
	for(int j=0; j<n; j++) 
	{
		remaining_time[j] = p[j].burst_time;
	}
	printf("\nGantt Chart:\n");
	
	while(i != n) 
	{						

		for(int j=0; j<n; j++) 
		{
			if(p[j].arrival_time <= current_time && remaining_time[j] >= 0) 
			{
				cnt++;
				if(remaining_time[j] < least_rt && remaining_time[j]>0) 
				{		
					k = j;
					least_rt = remaining_time[j];	
				}
			}
		}

		if(cnt == n) 
		{				
				printf("%d <---P%d---> ", current_time, p[k].p_no);
				current_time = current_time + remaining_time[k];
				remaining_time[k] = 0;
				p[k].turnaround_time = current_time - p[k].arrival_time;
				p[k].wait_time = p[k].turnaround_time - p[k].burst_time;
				
				total_tat += p[k].turnaround_time;
				total_wt += p[k].wait_time;
				i++;
		}
		else 
		{ 					
			printf("%d <---P%d---> ", current_time, p[k].p_no);
			current_time += 1;				//to check whether the newly arrived process has shorter burst 
			remaining_time[k] -= 1;			//time than the remaining time of the executing process
			if(remaining_time[k] == 0) 
			{
				p[k].turnaround_time = current_time - p[k].arrival_time;
				p[k].wait_time = p[k].turnaround_time - p[k].burst_time;
				total_tat += p[k].turnaround_time;
				total_wt += p[k].wait_time;
				i++;
			}
		}

		cnt = 0;
		least_rt = 9999;
	}

	printf("%d",current_time);

	printf("\n\nProcess\tArrival\tBurst\tTurnaround\tWait\n");
	printf("\tTime\tTime\tTime\t\tTime\n");
	for(int i=0; i<n; i++) 
	{
		printf("P%d\t%d\t%d\t%d\t\t%d\n", p[i].p_no, p[i].arrival_time, p[i].burst_time, p[i].turnaround_time, p[i].wait_time);
	}
	float avg_tat=(float)total_tat/n;
	float avg_wt=(float)total_wt/n;
	printf("\nTotal Turn around time = %d\n",total_tat);
	printf("\nAverage Turn around time = %.2f\n",avg_tat);
	printf("\nTotal Waiting time = %d\n",total_wt);
	printf("\nAverage Waiting time = %.2f\n",avg_wt);
}
