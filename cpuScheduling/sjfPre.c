#include <stdio.h>
#include <limits.h>
typedef struct
{
    int id;  // Process ID
    int at;  // Arrival Time
    int bt;  // Burst Time
    int ct;  // Completion Time
    int tat; // Turnaround Time
    int wt;  // Waiting Time
    int rt;  // Remaining Time
} Process;
void calculateTimes(Process p[], int n)
{
    int currentTime = 0, completed = 0, min_rt, idx = -1;
    int ganttChart[200], timeStamps[200], gcIdx = 0;
    // Initialize remaining time for all processes
    for (int i = 0; i < n; i++)
    {
        p[i].rt = p[i].bt;
    }
    while (completed < n)
    {
        min_rt = INT_MAX;
        idx = -1;
        // Find process with the shortest remaining time that has arrived
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= currentTime && p[i].rt > 0 && p[i].rt < min_rt)
            {
                min_rt = p[i].rt;
                idx = i;
            }
        }
        if (idx != -1)
        {
            // Process the selected job for 1 unit of time
            ganttChart[gcIdx] = p[idx].id;
            timeStamps[gcIdx] = currentTime;
            gcIdx++;
            currentTime++;
            p[idx].rt--;
            // If process is completed
            if (p[idx].rt == 0)
            {
                p[idx].ct = currentTime;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                completed++;
            }
        }
        else
        {
            // If no process is ready to execute, increment time
            ganttChart[gcIdx] = -1; // Idle state
            timeStamps[gcIdx] = currentTime;
            gcIdx++;
            currentTime++;
        }
    }
    timeStamps[gcIdx] = currentTime; // Final timestamp
    // Print Gantt Chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < gcIdx; i++)
    {
        if (i == 0 || ganttChart[i] != ganttChart[i - 1])
        {
            printf(" ------");
        }
    }
    printf("\n|");
    for (int i = 0; i < gcIdx; i++)
    {
        if (i == 0 || ganttChart[i] != ganttChart[i - 1])
        {
            if (ganttChart[i] == -1)
            {
                printf(" IDLE |");
            }
            else
            {
                printf(" P%-3d |", ganttChart[i]);
            }
        }
    }
    printf("\n");
    for (int i = 0; i < gcIdx; i++)
    {
        if (i == 0 || ganttChart[i] != ganttChart[i - 1])
        {
            printf(" ------");
        }
    }
    printf("\n%d", timeStamps[0]);
    for (int i = 1; i <= gcIdx; i++)
    {
        if (i == gcIdx || ganttChart[i] != ganttChart[i - 1])
        {
            printf(" %d", timeStamps[i]);
        }
    }
    printf("\n");
}
void printTable(Process p[], int n)
{
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
}
int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1; // Process ID
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
    }
    calculateTimes(p, n);
    printTable(p, n);
    return 0;
}