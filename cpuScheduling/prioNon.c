#include <stdio.h>
#define MAX 10

// Structure to store process details
struct Process {
    int pid; // Process ID
    int at;  // Arrival time
    int bt;  // Burst time
    int ct;  // Completion time
    int wt;  // Waiting time
    int tat; // Turnaround time
    int pri; // Priority
    int start; // Start time (for Gantt chart)
};

// Function to calculate waiting time and turnaround time
void calculateTimes(struct Process processes[], int n, struct Process gantt[], int *ganttLen) {
    int completed = 0, time = 0, idx, minPriority;
    int isCompleted[MAX] = {0};
    int prevTime = 0;
    *ganttLen = 0;

    // Sorting based on arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].at > processes[j].at) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    while (completed < n) {
        minPriority = 9999;
        idx = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= time && !isCompleted[i]) {
                if (processes[i].pri < minPriority) {
                    minPriority = processes[i].pri;
                    idx = i;
                }
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        // Process is executing
        processes[idx].start = time;
        processes[idx].ct = time + processes[idx].bt;
        processes[idx].tat = processes[idx].ct - processes[idx].at;
        processes[idx].wt = processes[idx].tat - processes[idx].bt;
        isCompleted[idx] = 1;
        completed++;
        // Add to Gantt chart
        gantt[*ganttLen] = processes[idx];
        (*ganttLen)++;
        time = processes[idx].ct;
    }
}

// Function to display the Gantt chart
void displayGanttChart(struct Process gantt[], int ganttLen) {
    printf("\nGantt Chart:\n ");
    // Top bar
    for (int i = 0; i < ganttLen; i++) {
        for (int j = 0; j < gantt[i].bt; j++) printf("--");
        printf(" ");
    }
    printf("\n|");
    // Process IDs
    for (int i = 0; i < ganttLen; i++) {
        for (int j = 0; j < gantt[i].bt - 1; j++) printf(" ");
        printf("P%d", gantt[i].pid);
        for (int j = 0; j < gantt[i].bt - 1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");
    // Bottom bar
    for (int i = 0; i < ganttLen; i++) {
        for (int j = 0; j < gantt[i].bt; j++) printf("--");
        printf(" ");
    }
    printf("\n");
    // Time markers
    int current = gantt[0].start;
    printf("%d", current);
    for (int i = 0; i < ganttLen; i++) {
        for (int j = 0; j < gantt[i].bt; j++) printf("  ");
        current = gantt[i].ct;
        if (current > 9) printf("\b"); // adjust spacing for 2-digit numbers
        printf("%d", current);
    }
    printf("\n");
}

// Function to display the results
void displayResults(struct Process processes[], int n) {
    printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    float totalWt = 0, totalTat = 0;
    for (int i = 0; i < n; i++) {
        totalWt += processes[i].wt;
        totalTat += processes[i].tat;
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].pid, processes[i].at, processes[i].bt, processes[i].pri, processes[i].ct,
               processes[i].wt, processes[i].tat);
    }
    printf("\nAverage Waiting Time: %.2f\n", totalWt / n);
    printf("Average Turnaround Time: %.2f\n", totalTat / n);
}

int main() {
    int n;
    struct Process processes[MAX], gantt[MAX];
    int ganttLen;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time, burst time, and priority for Process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].at, &processes[i].bt, &processes[i].pri);
        processes[i].ct = 0;
    }

    // Calculate times and build Gantt chart
    calculateTimes(processes, n, gantt, &ganttLen);

    // Display Gantt chart
    displayGanttChart(gantt, ganttLen);

    // Display the results
    displayResults(processes, n);

    return 0;
}
