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
	printf("\nEnter the total resource instances for each resource:");
	for (int i=0; i<r; i++)
    {
		printf("\nResource %d : ", i+1);
		scanf("%d", &available[i]);
	}
	printf("\nEnter the maximum number of resources for each process:");
	for (int i=0; i<n; i++)
	{
		printf("\nProcess %d\n", i+1);
		for (int j=0; j<r; j++)
		{
			printf("\nNumber of instance of resource %d it requires: ", j+1);
			scanf("%d", &max[i][j]);
		}
	}
	printf("\nEnter the resources allocated to each process:");
	for (int i=0; i<n; i++)
	{
		printf("\nProcess %d\n", i+1);
		for (int j=0; j<r; j++)
		{
			printf("\nInstance of resource %d allocated:", j+1);
			scanf("%d", &allocated[i][j]);
			need[i][j] = max[i][j] - allocated[i][j];
			available[j] = available[j] - allocated[i][j];
		}
	}
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
    printf("\n\tALLOCATED \n");
	for(int i=0; i<n; i++)
    {
		for(int j=0; j<r; j++)
		{
			printf("\t%d",allocated[i][j]);
		}
		printf("\n");
    }
    printf("\n\tMAXIMUM \n");
    for(int i=0;i<n;i++)
    {
        for(int j=0; j<r; j++)
		{
			printf("\t%d",max[i][j]);
		}
		printf("\n");
    }
    printf("\n\tNEED\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0; j<r; j++)
		{
			printf("\t%d",need[i][j]);
		}
		printf("\n");
        
    }
	printf("\n\tAVAILABLE\n");
	for(int i=0;i<n;i++)
	{
	    for(int j=0; j<r; j++){
		printf("\t%d", available[j]);
	        
	    }
	   printf("\n");
	}
}

void req_resource()
{
	int req[100] = {0};
	int id;
	printf("\nEnter the Process ID:\n");
	scanf("%d", &id);
	for(int i=0; i<r; i++)
    {
		printf("\nAdditional resource %d required:", i+1);
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
	printf("\nEnter the number of Processes:");
	scanf("%d",&n);
	printf("\nEnter the number of Resources:");
	scanf("%d",&r);
	int ch;
	bool f;
	do
    {
		printf("\nMENU");
		printf("\n1. Create\n2. Display\n3. Request More Resources\n4. Check Safety\n5. Exit\n");
        printf("\nEnter your choice:");
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
				printf("\nThe Safe Sequence is:\n");
					for(int i=0; i<n; i++)
					{
						printf("P%d", safe[i]);
						if(i == n-1)
                            printf("\n");
						else
                            printf("\t->\t");
					}
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
					printf("\nThe Safe Sequence is:\n");
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
				printf("\nWrong Choice\n");
				break;
		}
	}while(ch!=5);
	return 0;
}
