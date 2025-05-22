#include <stdio.h>
typedef struct
{
    int id;        // Process ID
    int at;        // Arrival Time
    int bt;        // Burst Time
    int ct;        // Completion Time
    int tat;       // Turnaround Time
    int wt;        // Waiting Time
    int completed; // Flag to check if process is completed
} Process;
void calculateTimes(Process p[], int n)
{
    int currentTime = 0, completed = 0;
    int ganttOrder[n], goIdx = 0;
    while (completed < n)
    {
        int min_bt = 1e9, idx = -1;
        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= currentTime && !p[i].completed && p[i].bt < min_bt)
            {
                min_bt = p[i].bt;
                idx = i;
            }
        }
        if (idx != -1)
        {
            // Process the selected job
            ganttOrder[goIdx++] = p[idx].id; // Add to Gantt order
            currentTime += p[idx].bt;
            p[idx].ct = currentTime;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].completed = 1; // Mark process as completed
            completed++;
        }
        else
        {
            // If no process has arrived yet, increment time
            currentTime++;
        }
    }
    // Print the Gantt Chart
    printf("\nGantt Chart:\n");
    printf(" ");
    for (int i = 0; i < goIdx; i++)
    {
        printf("-------");
    }
    printf("\n|");
    for (int i = 0; i < goIdx; i++)
    {
        printf(" P%-3d |", ganttOrder[i]);
    }
    printf("\n ");
    for (int i = 0; i < goIdx; i++)
    {
        printf("-------");
    }
    printf("\n0");
    currentTime = 0;
    for (int i = 0; i < goIdx; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (p[j].id == ganttOrder[i])
            {
                currentTime += p[j].bt;
                printf(" %d", currentTime);
                break;
            }
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
        p[i].id = i + 1;    // Process ID
        p[i].completed = 0; // Initially, no process is completed
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