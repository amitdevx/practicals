#include <stdio.h>
#include <stdbool.h>

int main() {
    int ref[] = {3, 5, 7, 2, 5, 1, 2, 3, 1, 3, 5, 3, 1, 6, 2};
    int n = sizeof(ref) / sizeof(ref[0]);
    int frames_count = 3;

    printf("LRU (Counter Method) Page Replacement Simulation\n");
    printf("Number of Frames: %d\n", frames_count);
    printf("Reference String Length: %d\n\n", n);

    int frames[10];
    int counter[10]; // Time of last access for each frame
    for (int i = 0; i < frames_count; i++) {
        frames[i] = -1;
        counter[i] = 0;
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
                counter[j] = timer; // update access time
                break;
            }
        }

        printf("%d\t%d\t[ ", i + 1, page);
        if (!found) {
            // Find empty frame or least recently used (smallest counter)
            int replace_idx = 0;
            int min_time = 1e9;

            for (int j = 0; j < frames_count; j++) {
                if (frames[j] == -1) {
                    replace_idx = j;
                    break;
                }
                if (counter[j] < min_time) {
                    min_time = counter[j];
                    replace_idx = j;
                }
            }

            frames[replace_idx] = page;
            counter[replace_idx] = timer;
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
