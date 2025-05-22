#include <stdio.h>
void firstFit(int blockSizes[], int m, int processSizes[], int n)
{
    int allocation[n];
    // Initialize allocation as -1 (not allocated)
    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }
    // Iterate over each process
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            // Find the first block that can fit the process
            if (blockSizes[j] >= processSizes[i])
            {
                allocation[i] = j;
                blockSizes[j] -= processSizes[i]; // Reduce available block size
                break;
            }
        }
    }
    // Display allocation
    printf("\nProcess No.\tProcess Size\tBlock Allocated\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, processSizes[i]);
        if (allocation[i] != -1)
        {
            printf("%d\n", allocation[i] + 1);
        }
        else
        {
            printf("Not Allocated\n");
        }
    }
}
int main()
{
    int m, n;
    // User input for number of blocks and processes
    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);
    int blockSizes[m];
    printf("Enter the sizes of the memory blocks:\n");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &blockSizes[i]);
    }
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processSizes[n];
    printf("Enter the sizes of the processes:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &processSizes[i]);
    }
    // Call First Fit function
    firstFit(blockSizes, m, processSizes, n);
    return 0;
}