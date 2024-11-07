#include <stdio.h>
#include <stdlib.h>

void fcfs(int requests[], int n, int head) {
    int seek_time = 0;
    printf("\nFCFS Disk Scheduling\n");
    printf("Seek Sequence: %d", head);
    
    for (int i = 0; i < n; i++) {
        seek_time += abs(requests[i] - head);
        head = requests[i];
        printf(" -> %d", head);
    }
    
    printf("\nTotal Seek Time: %d\n", seek_time);
}

void scan(int requests[], int n, int head, int disk_size, int direction) {
    int seek_time = 0;
    int left[100], right[100], l = 0, r = 0;

    // Adding requests on both sides of the head
    if (direction == 1) { // Right
        right[r++] = disk_size - 1;
    } else if (direction == -1) { // Left
        left[l++] = 0;
    }

    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {
            left[l++] = requests[i];
        } else if (requests[i] > head) {
            right[r++] = requests[i];
        }
    }

    // Sorting requests on left and right of the head
    for (int i = 0; i < l - 1; i++)
        for (int j = i + 1; j < l; j++)
            if (left[i] < left[j]) {
                int temp = left[i];
                left[i] = left[j];
                left[j] = temp;
            }

    for (int i = 0; i < r - 1; i++)
        for (int j = i + 1; j < r; j++)
            if (right[i] > right[j]) {
                int temp = right[i];
                right[i] = right[j];
                right[j] = temp;
            }

    printf("\nSCAN Disk Scheduling\n");
    printf("Seek Sequence: %d", head);

    if (direction == 1) { // Moving right
        for (int i = 0; i < r; i++) {
            seek_time += abs(right[i] - head);
            head = right[i];
            printf(" -> %d", head);
        }
        for (int i = 0; i < l; i++) {
            seek_time += abs(left[i] - head);
            head = left[i];
            printf(" -> %d", head);
        }
    } else { // Moving left
        for (int i = 0; i < l; i++) {
            seek_time += abs(left[i] - head);
            head = left[i];
            printf(" -> %d", head);
        }
        for (int i = 0; i < r; i++) {
            seek_time += abs(right[i] - head);
            head = right[i];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal Seek Time: %d\n", seek_time);
}

void cscan(int requests[], int n, int head, int disk_size) {
    int seek_time = 0;
    int left[100], right[100], l = 0, r = 0;

    // Add requests on both sides of the head
    right[r++] = disk_size - 1;
    left[l++] = 0;

    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {
            left[l++] = requests[i];
        } else if (requests[i] > head) {
            right[r++] = requests[i];
        }
    }

    // Sort requests on left and right of the head
    for (int i = 0; i < l - 1; i++)
        for (int j = i + 1; j < l; j++)
            if (left[i] < left[j]) {
                int temp = left[i];
                left[i] = left[j];
                left[j] = temp;
            }

    for (int i = 0; i < r - 1; i++)
        for (int j = i + 1; j < r; j++)
            if (right[i] > right[j]) {
                int temp = right[i];
                right[i] = right[j];
                right[j] = temp;
            }

    printf("\nC-SCAN Disk Scheduling\n");
    printf("Seek Sequence: %d", head);

    for (int i = 0; i < r; i++) {
        seek_time += abs(right[i] - head);
        head = right[i];
        printf(" -> %d", head);
    }

    head = 0;
    seek_time += disk_size - 1;

    for (int i = 0; i < l; i++) {
        seek_time += abs(left[i] - head);
        head = left[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Seek Time: %d\n", seek_time);
}

int main() {
    int n, head, disk_size, direction;
    
    printf("Enter number of requests: ");
    scanf("%d", &n);
    int requests[n];
    
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    printf("Enter direction (1 for high, -1 for low) for SCAN: ");
    scanf("%d", &direction);

    fcfs(requests, n, head);
    scan(requests, n, head, disk_size, direction);
    cscan(requests, n, head, disk_size);

    return 0;
}
