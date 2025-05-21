#include <stdio.h>

#define MAX 10

typedef struct {
    int id;
    int arrival_time;
    int execution_time;
    int period;
    int remaining_time;
    int next_arrival;
} Task;

int gcd(int a, int b) {
    return (b == 0) ? a : gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int find_hyperperiod(Task tasks[], int n) {
    int hyperperiod = tasks[0].period;
    for (int i = 1; i < n; i++) {
        hyperperiod = lcm(hyperperiod, tasks[i].period);
    }
    return hyperperiod;
}

void rate_monotonic(Task tasks[], int n) {
    int hyperperiod = find_hyperperiod(tasks, n);
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        tasks[i].next_arrival = tasks[i].arrival_time;
        tasks[i].remaining_time = tasks[i].execution_time;
    }

    printf("\n--- Rate Monotonic Scheduling Execution ---\n");

    while (current_time < hyperperiod) {
        int selected_task = -1;

        for (int i = 0; i < n; i++) {
            if (current_time >= tasks[i].next_arrival && tasks[i].remaining_time > 0) {
                if (selected_task == -1 || tasks[i].period < tasks[selected_task].period) {
                    selected_task = i;
                }
            }
        }

        if (selected_task != -1) {
            printf("[Time %d] Running Task %d\n", current_time, tasks[selected_task].id);
            tasks[selected_task].remaining_time--;

            if (tasks[selected_task].remaining_time == 0) {
                tasks[selected_task].next_arrival += tasks[selected_task].period;
                tasks[selected_task].remaining_time = tasks[selected_task].execution_time;
            }
        } else {
            printf("[Time %d] CPU Idle\n", current_time);
        }

        current_time++;
    }
}

int main() {
    int n;
    Task tasks[MAX];

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("\nTask %d:\n", tasks[i].id);
        printf("Arrival Time: ");
        scanf("%d", &tasks[i].arrival_time);
        printf("Execution Time: ");
        scanf("%d", &tasks[i].execution_time);
        printf("Period: ");
        scanf("%d", &tasks[i].period);
    }

    rate_monotonic(tasks, n);

    return 0;
}
