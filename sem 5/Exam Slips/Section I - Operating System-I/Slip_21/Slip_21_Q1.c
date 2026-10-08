#include <stdio.h>
#include <stdbool.h>

int main() {
    int frames_count;
    printf("Enter number of frames: ");
    if (scanf("%d", &frames_count) != 1 || frames_count <= 0) {
        frames_count = 3;
    }

    int ref[] = {8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2};
    int n = sizeof(ref) / sizeof(ref[0]);

    printf("\nMFU Page Replacement Simulation\n");
    printf("Number of Frames: %d\n", frames_count);
    printf("Reference String Length: %d\n\n", n);

    int frames[10];
    int freq[10];
    int arrival[10]; // to break ties using FIFO
    for (int i = 0; i < frames_count; i++) {
        frames[i] = -1;
        freq[i] = 0;
        arrival[i] = 0;
    }

    int page_faults = 0;
    int timer = 0;

    printf("Step\tPage\tFrames\t\tStatus\n");

    for (int i = 0; i < n; i++) {
        int page = ref[i];
        timer++;
        bool found = false;

        for (int j = 0; j < frames_count; j++) {
            if (frames[j] == page) {
                found = true;
                freq[j]++; // increase frequency on hit
                break;
            }
        }

        printf("%d\t%d\t[ ", i + 1, page);
        if (!found) {
            // Find empty frame or Most Frequently Used
            int replace_idx = -1;

            for (int j = 0; j < frames_count; j++) {
                if (frames[j] == -1) {
                    replace_idx = j;
                    break;
                }
            }

            if (replace_idx == -1) {
                int max_freq = -1;
                for (int j = 0; j < frames_count; j++) {
                    if (freq[j] > max_freq) {
                        max_freq = freq[j];
                        replace_idx = j;
                    } else if (freq[j] == max_freq) {
                        // Tie breaker: FIFO (oldest arrival)
                        if (arrival[j] < arrival[replace_idx]) {
                            replace_idx = j;
                        }
                    }
                }
            }

            frames[replace_idx] = page;
            freq[replace_idx] = 1; // reset frequency to 1 when brought in
            arrival[replace_idx] = timer;
            page_faults++;

            for (int j = 0; j < frames_count; j++) {
                if (frames[j] != -1) printf("%d ", frames[j]);
                else printf("- ");
            }
            printf("]\tPAGE FAULT\n");
        } else {
            for (int j = 0; j < frames_count; j++) {
                if (frames[j] != -1) printf("%d ", frames[j]);
                else printf("- ");
            }
            printf("]\tHIT\n");
        }
    }

    printf("Total Page Faults: %d\n", page_faults);
    printf("Total Hits: %d\n", n - page_faults);

    return 0;
}
