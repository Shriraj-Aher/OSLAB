#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
struct Process
{
    int id;      // Process ID
    int at;      // Arrival Time
    int bt;      // Burst Time
    int orig_bt; // Original Burst Time to calculate Waiting Time and Turnaround Time
    int pt;      // Priority (1 is highest)
    int ct;      // Completion Time
    int tat;     // Turnaround Time
    int wt;      // Waiting Time
};
int compare(const void *a, const void *b)
{
    return ((struct Process *)a)->at - ((struct Process *)b)->at;
}
int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process *processes = (struct Process *)malloc(n * sizeof(struct Process));
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1; // Process ID starts from 1
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].at, &processes[i].bt, &processes[i].pt);
        processes[i].orig_bt = processes[i].bt; // Store the original burst time
    }
    // Sort processes based on arrival time
    qsort(processes, n, sizeof(struct Process), compare);
    int currentTime = 0;
    int completed = 0;
    int isCompleted[n];
    int currentProcess = -1;
    // Initialize completed array
    for (int i = 0; i < n; i++)
    {
        isCompleted[i] = 0;
    }
    int gantt[100];      // Store process IDs for Gantt chart
    int gantt_time[100]; // Store time for each segment
    int gantt_index = 0;
    while (completed < n)
    {
        int idx = -1;
        int highestPriority = INT_MAX;
        // Find the process with the highest priority that has arrived
        for (int i = 0; i < n; i++)
        {
            if (processes[i].at <= currentTime && !isCompleted[i] && processes[i].bt > 0 &&
                processes[i].pt < highestPriority)
            {
                highestPriority = processes[i].pt;
                idx = i;
            }
        }
        if (idx != -1)
        {
            // Log the current process ID for Gantt chart
            if (currentProcess != idx)
            {
                if (currentProcess != -1)
                {
                    gantt[gantt_index] = processes[currentProcess].id;
                    gantt_time[gantt_index] = 1; // Add one time unit for the previous process
                    gantt_index++;
                }
                currentProcess = idx;
            }
            processes[currentProcess].bt--; // Decrease burst time
            currentTime++;
            // Add time to Gantt chart for the current process
            if (gantt_index > 0 && gantt[gantt_index - 1] == processes[currentProcess].id)
            {
                gantt_time[gantt_index - 1]++;
            }
            else
            {
                gantt[gantt_index] = processes[currentProcess].id;
                gantt_time[gantt_index] = 1;
                gantt_index++;
            }
            if (processes[currentProcess].bt == 0)
            {
                processes[currentProcess].ct = currentTime;
                processes[currentProcess].tat = processes[currentProcess].ct - processes[currentProcess].at;
                processes[currentProcess].wt = processes[currentProcess].tat -
                                               processes[currentProcess].orig_bt; // Use original burst time for wt calculation
                isCompleted[currentProcess] = 1;                                  // Mark process as completed
                completed++;
                currentProcess = -1; // Reset current process
            }
        }
        else
        {
            currentTime++; // Increment time if no process is ready to execute
        }
    }
    // Print results
printf("\nProcess\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n");
for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].at,
               processes[i].orig_bt, processes[i].pt, processes[i].ct, processes[i].tat, processes[i].wt);
}
// Display Gantt chart
printf("\nGantt Chart:\n");
for (int i = 0; i < gantt_index; i++) {
        printf(" P%d |", gantt[i]);
}
printf("\n");
// Print time line
int total_time = 0;
printf("%-5d", total_time);
for (int i = 0; i < gantt_index; i++) {
        total_time += gantt_time[i]; // Accumulate total time for each process
        printf(" %-5d", total_time);
}
printf("\n");
free(processes); // Free allocated memory
return 0;
}