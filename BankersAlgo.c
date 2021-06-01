#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LIMIT 100

int max[LIMIT][LIMIT];
int allocated[LIMIT][LIMIT];
int need[LIMIT][LIMIT];
int available[LIMIT];
int safe[LIMIT];
int n;
int r;

void create()
{
    printf("\n///////////////////////////////////////////////////////////////////\n");
	printf("\nEnter the total resource instances for each resource :- \n");
	for (int i=0; i<r; i++)
    {
		printf("\nResource %d :- \t", i+1);
		scanf("%d", &available[i]);
	}
	printf("\n///////////////////////////////////////////////////////////////////\n");
	printf("\nEnter the maximum number of resources for each process:- \n");
	for (int i=0; i<n; i++)
	{
		printf("\n______Process %d____\n", i+1);
		for (int j=0; j<r; j++)
		{
			printf("\nNumber of instance of resource %d it requires:\t", j+1);
			scanf("%d", &max[i][j]);
		}
	}
	printf("\n///////////////////////////////////////////////////////////////////\n");
	printf("\nEnter the resources allocated to each process :- \n");
	for (int i=0; i<n; i++)
	{
		printf("\n______Process %d____\n", i+1);
		for (int j=0; j<r; j++)
		{
			printf("\nInstance of resource %d allocated :- \t", j+1);
			scanf("%d", &allocated[i][j]);
			need[i][j] = max[i][j] - allocated[i][j];
			available[j] = available[j] - allocated[i][j];
		}
	}
	printf("\n///////////////////////////////////////////////////////////////////\n");
}

bool is_safe()
{
	bool end[LIMIT] = {false};
	int now[LIMIT];
	for (int i=0; i<r; i++)
    {
		now[i] = available[i];
	}
	int count = 0;
	while (count < n)
	{
		bool found = false;
		for (int p = 0; p < n; p++)
		{
            if (end[p] == false)
            {
                int j;
                for (j = 0; j < r; j++)
                {
                    if (need[p][j] > now[j]) break;
                }
                if (j == r)
                {
                    for (int k = 0 ; k < r ; k++)
                    {
                        now[k] += allocated[p][k];
                    }
                    safe[count++] = p;
                    end[p] = true;
                    found = true;
                }
            }
        }
        if (found == false) {
        	return false;
        }
	}
	return true;
}


void display()
{
	for(int i=0; i<n; i++)
    {
		printf("\n\n_____Process %d____\n", i+1);
		printf("\n\t\tALLOCATED \n");
		for(int j=0; j<r; j++)
		{
			printf("\tR%d - %d", j+1, allocated[i][j]);
			if (j != r-1) printf(", ");
		}
		printf("\n\t\tMAXIMUM \n");
		for(int j=0; j<r; j++)
		{
			printf("\tR%d - %d", j+1, max[i][j]);
			if (j != r-1) printf(", ");
		}
		printf("\n\t\tNEED\n");
		for(int j=0; j<r; j++)
		{
			printf("\tR%d - %d", j+1, need[i][j]);
			if (j != r-1) printf(", ");
		}
	}
	printf("\n_________________\n");
	printf("\n\t\tAVAILABLE\n");
	for(int j=0; j<r; j++)
    {
		printf("\tR%d - %d", j+1, available[j]);
		if (j != r-1) printf(", ");
	}
	printf("\n_________________\n");
}

void req_resource()
{
	int req[100] = {0};
	int id;
	printf("\nEnter the Process ID :- \n");
	scanf("%d", &id);
	for(int i=0; i<r; i++)
    {
		printf("\nAdditional resource %d required :- \t", i+1);
		scanf("%d", &req[i]);
		if(req[i] > need[id][i])
		{
			printf("\nrequest exceeds max.\n");
			return;
		}
        else if (req[i] > available[i])
        {
			printf("\nRequest for resources not available.\n Enter into WAIT state.\n");
			return;
		}
	}
	for(int i=0; i<r; i++)
    {
		available[i] = available[i] - req[i];
		allocated[id][i] = allocated[id][i] + req[i];
		need[id][i] = need[id][i] - req[i];
	}
	bool c = is_safe();
    if(c == false)
    {
        for(int i=0; i<r; i++)
        {
			available[i] = available[i] + req[i];
			allocated[id][i] = allocated[id][i] - req[i];
			need[id][i] = need[id][i] + req[i];
		}
		printf("\nSystem is not safe.\n request denied.\n Process enters WAIT state.\nSystem restored.\n");
	}
	else
    {
		printf("\nRequest Granted.\n");
	}
}


int main()
{
	printf("\nEnter the number of Processes :- \n");
	scanf("%d",&n);
	printf("\nEnter the number of Resources :- \n");
	scanf("%d",&r);
	int ch;
	bool f;
	do
    {
		printf("\n************** MENU ***************\n");
		printf("\n1. Create\n2. Display\n3. Request More Resources\n4. Check Safety\n5. Exit\n");
        printf("\n*****************************\n");
        printf("\nEnter your choice:- \n");
		scanf("%d", &ch);

		switch(ch)
		{
			case 1:
				create();
				break;
			case 2:
			    display();
				break;
			case 3:
				req_resource();
				break;
			case 4:
				f = is_safe();
				if(f == false)
                {
					printf("%s\n", "The System is not in safe state.\n");
				}
				else
                {
					printf("%s\n", "System is in safe state\n");
					printf("\nThe Safe Sequence is :- \n");
					for(int i=0; i<n; i++)
					{
						printf("P%d", safe[i]);
						if(i == n-1)
                            printf("\n");
						else
                            printf("\t->\t");
					}
				}
				break;
			case 5:
				break;
			default:
				printf("\nWrong Choice.\n");
				break;
		}
	}while(ch!=5);
	return 0;
}
