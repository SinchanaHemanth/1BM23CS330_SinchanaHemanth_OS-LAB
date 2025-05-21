#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 50

int memory[MAX_BLOCKS] = {0};

void sequential_allocation() {
    int start, length;
    printf("\nSequential Allocation\n");
    printf("Enter starting block and length of file: ");
    scanf("%d%d", &start, &length);

    int flag = 0;
    for (int i = start; i < start + length; i++) {
        if (memory[i] == 1) {
            flag = 1;
            break;
        }
    }

    if (flag == 0) {
        for (int i = start; i < start + length; i++) {
            memory[i] = 1;
        }
        printf("File allocated from block %d to %d\n", start, start + length - 1);
    } else {
        printf("Memory already in use. Allocation failed.\n");
    }
}

void indexed_allocation() {
    int index, n, blocks[MAX_BLOCKS];
    printf("\nIndexed Allocation\n");
    printf("Enter index block and number of blocks needed: ");
    scanf("%d%d", &index, &n);

    if (memory[index] == 1) {
        printf("Index block already allocated.\n");
        return;
    }

    int count = 0;
    printf("Enter block numbers:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &blocks[i]);
        if (memory[blocks[i]] == 0)
            count++;
    }

    if (count == n) {
        memory[index] = 1;
        for (int i = 0; i < n; i++) {
            memory[blocks[i]] = 1;
        }
        printf("File allocated at index block %d with blocks: ", index);
        for (int i = 0; i < n; i++) {
            printf("%d ", blocks[i]);
        }
        printf("\n");
    } else {
        printf("Some blocks already in use. Allocation failed.\n");
    }
}

typedef struct Block {
    int block_num;
    struct Block* next;
} Block;

void linked_allocation() {
    int start, n;
    printf("\nLinked Allocation\n");
    printf("Enter starting block and number of blocks needed: ");
    scanf("%d%d", &start, &n);

    if (memory[start] == 1) {
        printf("Starting block already allocated.\n");
        return;
    }

    Block* head = malloc(sizeof(Block));
    head->block_num = start;
    head->next = NULL;
    memory[start] = 1;

    Block* current = head;
    int block;
    for (int i = 1; i < n; i++) {
        printf("Enter next block: ");
        scanf("%d", &block);
        if (memory[block] == 1) {
            printf("Block %d already allocated. Allocation failed.\n", block);
            return;
        }
        memory[block] = 1;
        Block* new_block = malloc(sizeof(Block));
        new_block->block_num = block;
        new_block->next = NULL;
        current->next = new_block;
        current = new_block;
    }

    printf("File allocated using linked allocation: ");
    current = head;
    while (current != NULL) {
        printf("%d -> ", current->block_num);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    int choice;
    while (1) {
        printf("\nFile Allocation Strategies:\n");
        printf("1. Sequential Allocation\n");
        printf("2. Indexed Allocation\n");
        printf("3. Linked Allocation\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: sequential_allocation(); break;
            case 2: indexed_allocation(); break;
            case 3: linked_allocation(); break;
            case 4: exit(0);
            default: printf("Invalid choice\n");
        }
    }

    return 0;
}
