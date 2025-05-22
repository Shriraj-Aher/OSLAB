#include <stdio.h>
#include <stdlib.h>
void cscan(int requests[], int n, int st, int disk_size)
{
    int left = 0, right = 0;
    int distance = 0;
    int total_distance = 0;
    int left_arr[n], right_arr[n];
    int left_index = 0, right_index = 0;
    // Separate the requests into left and right of the initial head position
    for (int i = 0; i < n; i++)
    {
        if (requests[i] < st)
        {
            left_arr[left_index++] = requests[i];
        }
        else
        {
            right_arr[right_index++] = requests[i];
        }
    }
    // Sort the left and right arrays
    for (int i = 0; i < left_index - 1; i++)
    {
        for (int j = i + 1; j < left_index; j++)
        {
            if (left_arr[i] < left_arr[j])
            {
                int temp = left_arr[i];
                left_arr[i] = left_arr[j];
                left_arr[j] = temp;
            }
        }
    }
    for (int i = 0; i < right_index - 1; i++)
    {
        for (int j = i + 1; j < right_index; j++)
        {
            if (right_arr[i] > right_arr[j])
            {
                int temp = right_arr[i];
                right_arr[i] = right_arr[j];
                right_arr[j] = temp;
            }
        }
    }
    // Total distance calculation
    // Traverse the right side of the head
    total_distance += abs(st - right_arr[0]);
    distance = total_distance;
    for (int i = 0; i < right_index; i++)
    {
        printf("%d -> ", right_arr[i]);
        if (i == right_index - 1)
        {
            total_distance += abs(right_arr[i] - disk_size);
            distance = total_distance;
        }
        else
        {
            total_distance += abs(right_arr[i] - right_arr[i + 1]);
        }
    }
    // After reaching the maximum, go to the start of the disk (0) and process the left side
    total_distance += abs(disk_size - 0);
    for (int i = 0; i < left_index; i++)
    {
        printf("%d -> ", left_arr[i]);
        if (i == left_index - 1)
        {
            total_distance += abs(left_arr[i] - 0);
            distance = total_distance;
        }
        else
        {
            total_distance += abs(left_arr[i] - left_arr[i + 1]);
        }
    }
    printf("\nTotal distance: %d\n", total_distance);
    printf("Average Seek Distance: %.2f\n", (float)total_distance / n);
}
int main()
{
    int n, st, disk_size;
    // Input the number of requests, initial head position, and disk size
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
    printf("Enter the disk size: ");
    scanf("%d", &disk_size);
    // Call C-SCAN function
    cscan(requests, n, st, disk_size);
    return 0;
}