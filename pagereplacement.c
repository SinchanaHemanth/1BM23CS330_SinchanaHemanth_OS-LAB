#include <stdio.h>

#define MAX 100

int isPresent(int frames[], int page, int f) {
    for (int i = 0; i < f; i++) {
        if (frames[i] == page)
            return 1;
    }
    return 0;
}

void fifo(int pages[], int n, int f) {
    int frames[f], index = 0, pageFaults = 0;
    for (int i = 0; i < f; i++) frames[i] = -1;

    printf("\nFIFO Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        if (!isPresent(frames, pages[i], f)) {
            frames[index] = pages[i];
            index = (index + 1) % f;
            pageFaults++;
        }

        printf("Page %d: ", pages[i]);
        for (int j = 0; j < f; j++) {
            if (frames[j] != -1) printf("%d ", frames[j]);
            else printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults = %d\n", pageFaults);
}

void lru(int pages[], int n, int f) {
    int frames[f], time[f], pageFaults = 0;
    for (int i = 0; i < f; i++) frames[i] = -1;

    printf("\nLRU Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i], found = 0;

        for (int j = 0; j < f; j++) {
            if (frames[j] == page) {
                found = 1;
                time[j] = i;
                break;
            }
        }

        if (!found) {
            int lru = 0;
            for (int j = 1; j < f; j++) {
                if (frames[j] == -1 || time[j] < time[lru])
                    lru = j;
            }

            frames[lru] = page;
            time[lru] = i;
            pageFaults++;
        }

        printf("Page %d: ", page);
        for (int j = 0; j < f; j++) {
            if (frames[j] != -1) printf("%d ", frames[j]);
            else printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults = %d\n", pageFaults);
}

int predict(int pages[], int frames[], int f, int n, int index) {
    int res = -1, farthest = index;
    for (int i = 0; i < f; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n) return i;
    }
    return (res == -1) ? 0 : res;
}

void optimal(int pages[], int n, int f) {
    int frames[f], pageFaults = 0;
    for (int i = 0; i < f; i++) frames[i] = -1;

    printf("\nOptimal Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        if (!isPresent(frames, pages[i], f)) {
            int pos = -1;

            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            if (pos == -1)
                pos = predict(pages, frames, f, n, i + 1);

            frames[pos] = pages[i];
            pageFaults++;
        }

        printf("Page %d: ", pages[i]);
        for (int j = 0; j < f; j++) {
            if (frames[j] != -1) printf("%d ", frames[j]);
            else printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults = %d\n", pageFaults);
}

int main() {
    int pages[MAX], n, f;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);

    fifo(pages, n, f);
    lru(pages, n, f);
    optimal(pages, n, f);

    return 0;
}
