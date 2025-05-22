#include <stdio.h>
#include <stdbool.h>
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
void calculateTimes(Process p[], int n, int tq)
{
    int currentTime = 0, completed = 0;
    int ganttChart[200], timeStamps[200], gcIdx = 0;
    bool inQueue[100] = {false}; // To track if a process is in the ready queue
    // Initialize remaining times
    for (int i = 0; i < n; i++)
    {
        p[i].rt = p[i].bt;
    }
    // Queue simulation
    int queue[100], front = 0, rear = 0;
    queue[rear++] = 0; // Add the first process (assumes sorted by AT)
    inQueue[0] = true;
    while (completed < n)
    {
        int idx = queue[front++];
        if (front == 100)
            front = 0; // Circular queue
        // Add to Gantt Chart
        ganttChart[gcIdx] = p[idx].id;
        timeStamps[gcIdx++] = currentTime;
        // Process execution
        if (p[idx].rt <= tq)
        {
            currentTime += p[idx].rt;
            p[idx].rt = 0;
            p[idx].ct = currentTime;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
        }
        else
        {
            currentTime += tq;
            p[idx].rt -= tq;
        }
        // Check for newly arrived processes
        for (int i = 0; i < n; i++)
        {
            if (!inQueue[i] && p[i].at <= currentTime && p[i].rt > 0)
            {
                queue[rear++] = i;
                if (rear == 100)
                    rear = 0; // Circular queue
                inQueue[i] = true;
            }
        }
        // Re-add the current process to the queue if it is not completed
        if (p[idx].rt > 0)
        {
            queue[rear++] = idx;
            if (rear == 100)
                rear = 0; // Circular queue
        }
        // If the queue becomes empty and there are remaining processes, advance time
        if (front == rear)
        {
            for (int i = 0; i < n; i++)
            {
                if (p[i].rt > 0)
                {
                    queue[rear++] = i;
                    if (rear == 100)
                        rear = 0; // Circular queue
                    inQueue[i] = true;
                    break;
                }
            }
        }
    }
    // Final timestamp for Gantt Chart
    timeStamps[gcIdx] = currentTime;
    // Print Gantt Chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < gcIdx; i++)
    {
        printf(" ------");
    }
    printf("\n|");
    for (int i = 0; i < gcIdx; i++)
    {
        printf(" P%-3d |", ganttChart[i]);
    }
    printf("\n");
    for (int i = 0; i < gcIdx; i++)
    {
        printf(" ------");
    }
    printf("\n%d", timeStamps[0]);
    for (int i = 1; i <= gcIdx; i++)
    {
        printf(" %d", timeStamps[i]);
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
    int n, tq;
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
    printf("Enter the Time Quantum: ");
    scanf("%d", &tq);
    calculateTimes(p, n, tq);
    printTable(p, n);
    return 0;
}