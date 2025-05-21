#include <stdio.h>
#include <stdlib.h>

struct process {
    int id, AT, BT, CT, TAT, WT, remaining_BT, completed;
};

void calculate_SJF_NonPreemptive(struct process p[], int n) {
    int completed = 0, currentTime = 0;
    while (completed < n) {
        int shortest = -1, minBT = 10000;
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].AT <= currentTime && p[i].BT < minBT) {
                minBT = p[i].BT;
                shortest = i;
            }
        }
        if (shortest == -1) {
            currentTime++;
        } else {
            p[shortest].CT = currentTime + p[shortest].BT;
            currentTime = p[shortest].CT;
            p[shortest].TAT = p[shortest].CT - p[shortest].AT;
            p[shortest].WT = p[shortest].TAT - p[shortest].BT;
            p[shortest].completed = 1;
            completed++;
        }
    }
}

void calculate_SJF_Preemptive(struct process p[], int n) {
    int completed = 0, currentTime = 0, minBT = 10000, shortest = -1;
    for (int i = 0; i < n; i++) {
        p[i].remaining_BT = p[i].BT;
    }

    while (completed < n) {
        shortest = -1;
        minBT = 10000;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].AT <= currentTime && p[i].remaining_BT < minBT && p[i].remaining_BT > 0) {
                minBT = p[i].remaining_BT;
                shortest = i;
            }
        }

        if (shortest == -1) {
            currentTime++;
        } else {
            p[shortest].remaining_BT--;
            currentTime++;

            if (p[shortest].remaining_BT == 0) {
                p[shortest].CT = currentTime;
                p[shortest].TAT = p[shortest].CT - p[shortest].AT;
                p[shortest].WT = p[shortest].TAT - p[shortest].BT;
                p[shortest].completed = 1;
                completed++;
            }
        }
    }
}

void display(struct process p[], int n) {
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT);
    }
}

int main() {
    int n, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct process p[n], backup[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time (AT) for process %d: ", i + 1);
        scanf("%d", &p[i].AT);
        printf("Enter Burst Time (BT) for process %d: ", i + 1);
        scanf("%d", &p[i].BT);
        p[i].completed = 0;
        backup[i] = p[i];  // Backup for reuse
    }

    printf("\nChoose Scheduling Type:\n1. SJF Non-Preemptive\n2. SJF Preemptive (SRTF)\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        calculate_SJF_NonPreemptive(p, n);
    } else if (choice == 2) {
        calculate_SJF_Preemptive(p, n);
    } else {
        printf("Invalid choice!\n");
        return 0;
    }

    display(p, n);
    return 0;
}
