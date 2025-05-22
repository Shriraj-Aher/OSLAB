#include <stdio.h>
void nextFit(int blockSizes[], int m, int processSizes[], int n)
{
    int allocation[n];     // To track block allocated to each process
    int lastAllocated = 0; // To track the last block index used for allocation
    // Initialize all allocations to -1 (not allocated)
    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }
    // Iterate over each process to allocate memory
    for (int i = 0; i < n; i++)
    {
        int startIndex = lastAllocated; // Start from the last allocated block
        do
        {
            if (blockSizes[lastAllocated] >= processSizes[i])
            {
                allocation[i] = lastAllocated;                // Allocate the block to this process
                blockSizes[lastAllocated] -= processSizes[i]; // Reduce the block size
                break;                                        // Process allocated, move to the next process
            }
            lastAllocated = (lastAllocated + 1) % m; // Move to the next block (circular)
        } while (lastAllocated != startIndex); // Stop if we've looped back to the starting block
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
    // Call Next Fit allocation
    nextFit(blockSizes, m, processSizes, n);
    return 0;
}