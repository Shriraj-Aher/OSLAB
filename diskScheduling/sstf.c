#include <stdio.h>
#include <stdlib.h>
int findClosestRequest(int curr, int requests[], int n, int processed[])
{
    int minDistance = 1000000; // Arbitrary large number for comparison
    int index = -1;
    for (int i = 0; i < n; i++)
    {
        if (processed[i] == 0)
        { // Unprocessed request
            int distance = abs(curr - requests[i]);
            if (distance < minDistance)
            {
                minDistance = distance;
                index = i;
            }
        }
    }
    return index;
}
int main()
{
    int n, st, dist = 0;
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    int requests[n];
    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &st);
    int curr = st;
    int completed = 0;
    int processed[n];
    for (int i = 0; i < n; i++)
    {
        processed[i] = 0; // Initialize all requests as unprocessed
    }
    printf("\nDisk Scheduling Order (SSTF):\n");
    while (completed < n)
    {
        int index = findClosestRequest(curr, requests, n, processed);
        // If all requests have been processed, break out
        if (index == -1)
        {
            break;
        }
        // Process the closest request
        printf("Move from %d to %d, distance = %d\n", curr, requests[index], abs(curr - requests[index]));
        dist += abs(curr - requests[index]);
        curr = requests[index];
        processed[index] = 1; // Mark the request as processed
        completed++;
    }
    return 0;
    printf("\nTotal distance traveled by the disk arm: %d\n", dist);
    printf("Average Seek Distance: %.2f\n", (float)dist / n);
}