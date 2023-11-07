#include <stdio.h>

struct process
{
    int max[10], allocate[10], need[10];
} p[10];

int n, m;
void input(int[]);
void display(struct process p[]);
int isSafestate(int[], int[], struct process p[]);
int safetyalgorithm(int[], int[], struct process p[]);

int main()
{
    int i;
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int available[m];
    int safesequence[n];
    
    input(available);
    display(p);
    printf("\n\n");

    int flag = 1;
    while (flag)
    {
        printf("MENU\n1 - Find System Safety\n2 - Get Safe Sequence\n3 - Resource Request\n4 - Exit\n");
        printf("Enter a choice: ");
        int ch;
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            if (isSafestate(available, safesequence, p))
            {
                printf("\n\tSYSTEM IS IN SAFE STATE.\n\n");
            }
            else
                printf("\nSYSTEM IS IN UNSAFE STATE!!\n\n");
            break;
        case 2:
            printf("\n");
            if (isSafestate(available, safesequence, p))
            {
                printf("Safe Sequence is: \t");
                for (i = 0; i < n; i++)
                    printf("P%d -> ", safesequence[i]);
            }
            printf("\n\n");
            break;
        case 3:
            printf("Enter the Process no. for request: ");
            int proc;
            scanf("%d", &proc);

            // copying the processes
            struct process pc[10];

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    pc[i].max[j] = p[i].max[j];
                    pc[i].allocate[j] = p[i].allocate[j];
                    pc[i].need[j] = p[i].need[j];
                }
            }

            printf("Enter the resource requests: \n");

            for (int i = 0; i < m; i++)
            {
                int tp;
                scanf("%d", &tp);
                pc[proc].allocate[i] += tp;
                pc[proc].need[i] = pc[proc].max[i] - pc[proc].allocate[i];
            }

            if (isSafestate(available, safesequence, pc))
            {
                printf("\tSystem is Safe with given Resource Request!");
                printf("\n");
                if (isSafestate(available, safesequence, p))
                {
                    printf("Safe Sequence is: \t");
                    for (i = 0; i < n; i++)
                        printf("P%d -> ", safesequence[i]);
                }
                printf("\n\n");
            }
            else
                printf("\tSystem is Not Safe with given Resource Request!");

            printf("\n\n");
            break;
        case 4:
            printf("Exiting...\n\n");
            flag = 0;
            break;
        default:
            printf("Invalid Input.\n\n");
            break;
        }
    }

    return 0;
}

void input(int available[m])
{

    int i, j;
    for (i = 0; i < n; i++)
    {

        printf("\nProcess P%d:\n", i);
        printf("Enter the allocated resources: ");
        for (j = 0; j < m; j++)
        {
            scanf("%d", &p[i].allocate[j]);
        }
        printf("Enter the max resources: ");
        for (j = 0; j < m; j++)
        {
            scanf("%d", &p[i].max[j]);
            p[i].need[j] = p[i].max[j] - p[i].allocate[j];
        }
    }
    printf("\nEnter the available resources: ");
    for (j = 0; j < m; j++)
    {
        scanf("%d", &available[j]);
    }
}

void display(struct process p[])
{
    int i, j;
    printf("\n\tPID\tALLOCATE\tMAX\t\tNEED\n");
    for (i = 0; i < n; i++)
    {
        printf("\tP%d\t", i);
        for (j = 0; j < m; j++)
            printf("%d ", p[i].allocate[j]);
        printf("\t\t");
        for (j = 0; j < m; j++)
            printf("%d ", p[i].max[j]);
        printf("\t\t");
        for (j = 0; j < m; j++)
            printf("%d ", p[i].need[j]);
        printf("\n");
    }
}

int isSafestate(int available[m], int safesequence[n], struct process p[])
{
    if (safetyalgorithm(available, safesequence, p) == 1)
        return 1;
    return 0;
}

int safetyalgorithm(int available[m], int safesequence[n], struct process p[])
{
    int i, j;

    int work[m], finish[n];
    for (j = 0; j < m; j++)
        work[j] = available[j];

    for (i = 0; i < n; i++)
        finish[i] = 0;

    int proceed = 1, k = 0;
    while (proceed)
    {
        proceed = 0;
        for (i = 0; i < n; i++)
        {
            int flag = 1;
            if (finish[i] == 0)
            {
                for (j = 0; j < m; j++)
                {
                    if (p[i].need[j] <= work[j])
                    {
                        continue;
                    }
                    else
                    {
                        flag = 0;
                        break;
                    }
                }
                if (flag == 0)
                    continue;

                for (j = 0; j < m; j++)
                {
                    work[j] += p[i].allocate[j];
                }
                finish[i] = 1;
                safesequence[k++] = i;
                proceed = 1;
            }
        }
    }

    for (i = 0; i < n && finish[i] == 1; i++)
        continue;
    if (i == n)
        return 1;
    return 0;
}
