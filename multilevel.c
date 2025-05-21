#include <stdio.h>
#include <string.h>

struct process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    char type[10];  
    int started;    
    int finished;   
};

int allCompleted(struct process p[], int n) {
    for (int i = 0; i < n; i++) {
        if (!p[i].finished) return 0;
    }
    return 1;
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nProcess %d:\n", i + 1);
        printf("Enter Type (System/User): ");
        scanf("%s", p[i].type);
        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].arrivalTime);
        printf("Enter Burst Time: ");
        scanf("%d", &p[i].burstTime);
        p[i].remainingTime = p[i].burstTime;
        p[i].started = 0;
        p[i].finished = 0;
    }

    int currentTime = 0;

    printf("\n--- Execution Log ---\n");

    while (!allCompleted(p, n)) {
        int idx = -1;
        // Priority to system processes
        for (int i = 0; i < n; i++) {
            if (!p[i].finished && p[i].arrivalTime <= currentTime && 
                (strcmp(p[i].type, "System") == 0 || strcmp(p[i].type, "system") == 0)) {
                idx = i;
                break;
            }
        }

        if (idx == -1) {
            for (int i = 0; i < n; i++) {
                if (!p[i].finished && p[i].arrivalTime <= currentTime) {
                    idx = i;
                    break;
                }
            }
        }

        if (idx != -1) {
            printf("Time %d: Executing P%d (%s)\n", currentTime, p[idx].id, p[idx].type);
            p[idx].remainingTime--;

            if (p[idx].remainingTime == 0) {
                p[idx].completionTime = currentTime + 1;
                p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
                p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
                p[idx].finished = 1;
            }
        } else {
            printf("Time %d: CPU Idle\n", currentTime);
        }

        currentTime++;
    }

    printf("\n--- Final Process Table ---\n");
    printf("ID\tType\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].type, p[i].arrivalTime, p[i].burstTime,
               p[i].completionTime, p[i].turnaroundTime, p[i].waitingTime);
    }

    return 0;
}
