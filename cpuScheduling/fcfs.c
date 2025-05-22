#include <stdio.h>
typedef struct
{
    int id;  // Process ID
    int at;  // Arrival Time
    int bt;  // Burst Time
    int ct;  // Completion Time
    int tat; // Turnaround Time
    int wt;  // Waiting Time
} Process;
void calculateTimes(Process p[], int n)
{
    int currentTime = 0;
    for (int i = 0; i < n; i++)
    {
        if (currentTime < p[i].at)
        {
            currentTime = p[i].at; // If CPU is idle
        }
        p[i].ct = currentTime + p[i].bt; // Completion Time
        currentTime = p[i].ct;
        p[i].tat = p[i].ct - p[i].at; // Turnaround Time
        p[i].wt = p[i].tat - p[i].bt; // Waiting Time
    }
}
void printGanttChart(Process p[], int n)
{
    printf("\nGantt Chart:\n");
    // Top line
    printf(" ");
    for (int i = 0; i < n; i++)
    {
        printf("-------");
    }
    printf("\n");
    // Process line
    printf("|");
    for (int i = 0; i < n; i++)
    {
        printf(" P%-3d |", p[i].id);
    }
    printf("\n");
    // Bottom line
    printf(" ");
    for (int i = 0; i < n; i++)
    {
        printf("-------");
    }
    printf("\n");
    // Time line
    printf("0");
    for (int i = 0; i < n; i++)
    {
        printf(" %d", p[i].ct);
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
    // Sort processes by arrival time (FCFS rule)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].at > p[j].at)
            {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    calculateTimes(p, n);
    printTable(p, n);
    printGanttChart(p, n);
    return 0;
}