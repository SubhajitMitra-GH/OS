#include <stdio.h>
#include <limits.h>

void fifo(int pages[], int n, int capacity) {
    int frames[capacity];
    int pageFaults = 0, index = 0;

    for (int i = 0; i < capacity; i++)
        frames[i] = -1; // Initialize frames as empty

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frames[index] = pages[i];
            index = (index + 1) % capacity;
            pageFaults++;
        }
    }

    printf("FIFO Page Faults: %d\n", pageFaults);
}

void lru(int pages[], int n, int capacity) {
    int frames[capacity];
    int pageFaults = 0;
    int counter = 0;
    int time[capacity];

    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                time[j] = ++counter;
                break;
            }
        }

        if (!found) {
            int lruIndex = 0;
            for (int j = 1; j < capacity; j++) {
                if (time[j] < time[lruIndex]) {
                    lruIndex = j;
                }
            }
            frames[lruIndex] = pages[i];
            time[lruIndex] = ++counter;
            pageFaults++;
        }
    }

    printf("LRU Page Faults: %d\n", pageFaults);
}

void lfu(int pages[], int n, int capacity) {
    int frames[capacity];
    int frequency[capacity];
    int pageFaults = 0;

    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
        frequency[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                frequency[j]++;
                break;
            }
        }

        if (!found) {
            int lfuIndex = 0;
            for (int j = 1; j < capacity; j++) {
                if (frequency[j] < frequency[lfuIndex] || (frequency[j] == frequency[lfuIndex] && frames[j] == -1)) {
                    lfuIndex = j;
                }
            }

            frames[lfuIndex] = pages[i];
            frequency[lfuIndex] = 1;
            pageFaults++;
        }
    }

    printf("LFU Page Faults: %d\n", pageFaults);
}

int main() {
    int n, capacity;

    printf("Enter the number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter the pages: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    fifo(pages, n, capacity);
    lru(pages, n, capacity);
    lfu(pages, n, capacity);

    return 0;
}
