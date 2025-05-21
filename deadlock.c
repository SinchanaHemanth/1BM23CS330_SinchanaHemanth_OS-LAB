#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int n, m; 

int allocation[MAX_PROCESSES][MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];

int safe_sequence[MAX_PROCESSES];

int is_safe() {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};

    for (int i = 0; i < m; i++)
        work[i] = available[i];

    int count = 0;

    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j])
                        break;
                }

                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += allocation[i][k];
                    safe_sequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            return 0; 
        }
    }

    return 1; 
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);
    }

    printf("\nEnter Maximum Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++)
            scanf("%d", &maximum[i][j]);
    }

    printf("\nEnter Available Resources: ");
    for (int i = 0; i < m; i++)
        scanf("%d", &available[i]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = maximum[i][j] - allocation[i][j];

    if (is_safe()) {
        printf("\nSystem is in a SAFE state.\nSafe sequence is: ");
        for (int i = 0; i < n; i++)
            printf("P%d ", safe_sequence[i]);
        printf("\n");
    } else {
        printf("\nSystem is in an UNSAFE state. Deadlock may occur.\n");
    }

    return 0;
}
