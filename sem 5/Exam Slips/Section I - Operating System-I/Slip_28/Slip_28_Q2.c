#include <stdio.h>
#include <stdbool.h>

int main() {
    int ref[] = {8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2};
    int n = sizeof(ref) / sizeof(ref[0]);
    int frames_count = 3;

    printf("MFU (Most Frequently Used) Page Replacement Simulation\n");
    printf("Number of Frames: %d\n", frames_count);
    printf("Reference String Length: %d\n\n", n);

    int frames[10];
    int count[10]; // Frequency of access
    for (int i = 0; i < frames_count; i++) {
        frames[i] = -1;
        count[i] = 0;
    }

    int page_faults = 0;

    printf("Step\tPage\tFrames\t\tStatus\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        int page = ref[i];
        bool found = false;

        for (int j = 0; j < frames_count; j++) {
            if (frames[j] == page) {
                found = true;
                count[j]++;
                break;
            }
        }

        printf("%d\t%d\t[ ", i + 1, page);
        if (!found) {
            int replace_idx = -1;
            // Check for free frame
            for (int j = 0; j < frames_count; j++) {
                if (frames[j] == -1) {
                    replace_idx = j;
                    break;
                }
            }

            // If no free frame, replace frame with maximum frequency
            if (replace_idx == -1) {
                int max_freq = -1;
                for (int j = 0; j < frames_count; j++) {
                    if (count[j] > max_freq) {
                        max_freq = count[j];
                        replace_idx = j;
                    }
                }
            }

            frames[replace_idx] = page;
            count[replace_idx] = 1;
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

    printf("-------------------------------------------------\n");
    printf("Total Page Faults: %d\n", page_faults);
    printf("Total Hits: %d\n", n - page_faults);

    return 0;
}
