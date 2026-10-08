#include <stdio.h>
#include <stdbool.h>

int main() {
    int ref[] = {3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6};
    int n = sizeof(ref) / sizeof(ref[0]);
    int frames_count = 3;

    printf("FIFO Page Replacement Simulation\n");
    printf("Number of Frames: %d\n", frames_count);
    printf("Reference String Length: %d\n\n", n);

    int frames[10];
    for (int i = 0; i < frames_count; i++) frames[i] = -1;

    int page_faults = 0;
    int next_replace_idx = 0;

    printf("Step\tPage\tFrames\t\tStatus\n");

    for (int i = 0; i < n; i++) {
        int page = ref[i];
        bool found = false;

        for (int j = 0; j < frames_count; j++) {
            if (frames[j] == page) {
                found = true;
                break;
            }
        }

        printf("%d\t%d\t[ ", i + 1, page);
        if (!found) {
            frames[next_replace_idx] = page;
            next_replace_idx = (next_replace_idx + 1) % frames_count;
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
