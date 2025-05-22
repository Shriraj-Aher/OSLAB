#include <stdio.h>
#include <limits.h> // For INT_MAX
void bestFit(int blockSizes[], int m, int processSizes[], int n)
{
    int allocation[n]; // To track block allocated to each process
    // Initialize all allocations to -1 (not allocated)
    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }
    // Iterate over each process to allocate memory
    for (int i = 0; i < n; i++)
    {
        int bestIdx = -1; // Initialize the best fit block index
        for (int j = 0; j < m; j++)
        {
            if (blockSizes[j] >= processSizes[i])
            {
                if (bestIdx == -1 || blockSizes[j] < blockSizes[bestIdx])
                {
                    bestIdx = j; // Update the best fit block index
                }
            }
        }
        // If a suitable block is found
        if (bestIdx != -1)
        {
            allocation[i] = bestIdx;                // Allocate the block to the process
            blockSizes[bestIdx] -= processSizes[i]; // Reduce the block size
        }
    }
    // Display the results
    printf("\nProcess No.\tProcess Size\tBlock Allocated\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, processSizes[i]);
        if (allocation[i] != -1)
        {
            printf("%d\n", allocation[i] + 1); // Display 1-based block index
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
    // Input for number of memory blocks and their sizes
    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);
    int blockSizes[m];
    printf("Enter the sizes of the memory blocks:\n");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &blockSizes[i]);
    }
    // Input for number of processes and their sizes
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processSizes[n];
    printf("Enter the sizes of the processes:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &processSizes[i]);
    }   
    // Call Best Fit allocation
    bestFit(blockSizes, m, processSizes, n);
    return 0;
}