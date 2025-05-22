#include <stdio.h>
#define MAX 10
// Structure to store process details
struct Process
{
    int pid; // Process ID
    int at;  // Arrival time
    int bt;  // Burst time
    int ct;  // Completion time
    int wt;  // Waiting time
    int tat; // Turnaround time
    int rt;  // Remaining time
};
// Function to find the process with the shortest remaining time
int findShortestRemainingTime(struct Process processes[], int n, int time)
{
    int min = -1;
    int minIndex = -1;
    for (int i = 0; i < n; i++)
    {
        if (processes[i].at <= time && processes[i].rt > 0)
        {
            if (min == -1 || processes[i].rt < min)
            {
                min = processes[i].rt;
                minIndex = i;
            }
        }
    }
    return minIndex;
}
// Function to calculate waiting time and turnaround time
void calculateTimes(struct Process processes[], int n)
{
    int time = 0;
    int completed = 0;
    // Initialize remaining time
    for (int i = 0; i < n; i++)
    {
        processes[i].rt = processes[i].bt;
    }
    // Loop to execute all processes
    while (completed < n)
    {
        // Find the process with the shortest remaining time
        int idx = findShortestRemainingTime(processes, n, time);
        if (idx == -1)
        {
            time++; // If no process is ready to execute, just increment time
            continue;
        }
        // Process is executing
        processes[idx].rt--; // Decrease the remaining time
        // If process is completed
        if (processes[idx].rt == 0)
        {
            completed++;
            processes[idx].ct = time + 1;
            processes[idx].tat = processes[idx].ct - processes[idx].at;
            processes[idx].wt = processes[idx].tat - processes[idx].bt;
        }
        time++; // Move time forward
    }
}
// Function to display the results
void displayResults(struct Process processes[], int n)
{
printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
float totalWt = 0, totalTat = 0;
for (int i = 0; i < n; i++) {
        totalWt += processes[i].wt;
        totalTat += processes[i].tat;
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].pid, processes[i].at, processes[i].bt, processes[i].ct, processes[i].wt,
               processes[i].tat);
}
printf("\nAverage Waiting Time: %.2f\n", totalWt / n);
printf("Average Turnaround Time: %.2f\n", totalTat / n);
}
int main()
{
    int n;
    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
    // Input process details
    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1; // Process ID
        printf("Enter arrival time and burst time for Process %d: ", i + 1);
        scanf("%d %d", &processes[i].at, &processes[i].bt);
    }
    // Calculate completion time, waiting time, and turnaround time
    calculateTimes(processes, n);
    // Display the results
    displayResults(processes, n);
    return 0;
}