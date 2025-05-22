#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
bool isSafe(int **max, int **alloc, int *avail, int process, int numResources)
{
    int *need = (int *)malloc(numResources * sizeof(int));
    for (int i = 0; i < numResources; i++)
    {
        need[i] = max[process][i] - alloc[process][i];
    }
    for (int i = 0; i < numResources; i++)
    {
        if (need[i] > avail[i])
        {
            free(need); // Free the allocated memory for 'need'
            return false;
        }
    }
    free(need); // Free the allocated memory for 'need'
    return true;
}
bool bankersAlgorithm(int **max, int **alloc, int *avail, int numProcesses, int numResources)
{
    bool *finish = (bool *)malloc(numProcesses * sizeof(bool));
    int *safeSequence = (int *)malloc(numProcesses * sizeof(int));
    int numFinished = 0;
    for (int i = 0; i < numProcesses; i++)
    {
        finish[i] = false;
    }
    int safeSequenceIndex = 0;
    while (numFinished < numProcesses)
    {
        bool found = false;
        for (int i = 0; i < numProcesses; i++)
        {
            if (!finish[i] && isSafe(max, alloc, avail, i, numResources))
            {
                for (int j = 0; j < numResources; j++)
                {
                    avail[j] += alloc[i][j];
                }
                safeSequence[safeSequenceIndex++] = i;
                finish[i] = true;
                numFinished++;
                found = true;
            }
        }
        if (!found)
        {
            free(finish);
            free(safeSequence);
            return false;
        }
    }
    printf("Safe sequence: ");
    for (int i = 0; i < safeSequenceIndex; i++)
    {
        printf("P%d", safeSequence[i]);
        if (i < safeSequenceIndex - 1)
        {
            printf(" -> ");
        }
    }
    printf("\n");
    free(finish);
    free(safeSequence);
    return true;
}
int main()
{
    int numProcesses, numResources;
    printf("Number of processes: ");
    scanf("%d", &numProcesses);
    printf("Number of resources: ");
    scanf("%d", &numResources);
    int **max = (int **)malloc(numProcesses * sizeof(int *));
    int **alloc = (int **)malloc(numProcesses * sizeof(int *));
    int *avail = (int *)malloc(numResources * sizeof(int));
    for (int i = 0; i < numProcesses; i++)
    {
        max[i] = (int *)malloc(numResources * sizeof(int));
        alloc[i] = (int *)malloc(numResources * sizeof(int));
    }
    printf("Enter the maximum resource matrix:\n");
    for (int i = 0; i < numProcesses; i++)
    {
        for (int j = 0; j < numResources; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < numProcesses; i++)
    {
        for (int j = 0; j < numResources; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }
    printf("Enter the available resource vector:\n");
    for (int i = 0; i < numResources; i++)
    {
        scanf("%d", &avail[i]);
    }
    if (bankersAlgorithm(max, alloc, avail, numProcesses, numResources))
    {
        printf("System is in a safe state.\n");
    }
    else
    {
        printf("System is in an unsafe state.\n");
    }
    for (int i = 0; i < numProcesses; i++)
    {
        free(max[i]);
        free(alloc[i]);
    }
    free(max);
    free(alloc);
    free(avail);
    return 0;
}