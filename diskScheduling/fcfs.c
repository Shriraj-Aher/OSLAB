#include <stdio.h>
#include <stdlib.h>
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
    printf("\nDisk Scheduling Order (FCFS):\n");
    for (int i = 0; i < n; i++)
    {
        printf("Move from %d to %d, distance = %d\n", curr, requests[i], abs(requests[i] - curr));
        dist += abs(requests[i] - curr);
        curr = requests[i];
    }
    printf("\nTotal distance traveled by the disk arm: %d\n", dist);
    printf("Average Seek Distance: %.2f\n", (float)dist / n);
    return 0;
}