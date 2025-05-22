1 SSTF

#include <stdio.h>
#include <stdlib.h>

int findClosestRequest(int curr, int requests[], int n, int processed[]) {
    int minDistance = 1000000;
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (processed[i] == 0) {
            int distance = abs(curr - requests[i]);
            if (distance < minDistance) {
                minDistance = distance;
                index = i;
            }
        }
    }
    return index;
}

int main() {
    int n, st, dist = 0, total_latency = 0;
    const int rotational_latency = 2; // ms

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &st);

    int curr = st, completed = 0;
    int processed[n];
    for (int i = 0; i < n; i++) processed[i] = 0;

    printf("\n%-15s %-15s %-15s %-15s\n", "Current", "Next", "Seek Dist", "Total Latency (ms)");
    printf("---------------------------------------------------------------\n");

    while (completed < n) {
        int index = findClosestRequest(curr, requests, n, processed);
        if (index == -1) break;

        int seek = abs(curr - requests[index]);
        int latency = seek + rotational_latency;

        printf("%-15d %-15d %-15d %-15d\n", curr, requests[index], seek, latency);

        dist += seek;
        total_latency += latency;
        curr = requests[index];
        processed[index] = 1;
        completed++;
    }

    printf("\nTotal distance (seek): %d tracks\n", dist);
    printf("Average seek distance: %.2f tracks\n", (float)dist / n);
    printf("Total latency: %d ms\n", total_latency);
    printf("Average latency per request: %.2f ms\n", (float)total_latency / n);

    return 0;
}
OUTPUT :

Enter the number of disk requests: 5
Enter the disk requests: 82 170 43 140 24
Enter the initial head position: 50

Current         Next            Seek Dist       Total Latency (ms)
---------------------------------------------------------------
50              43              7               9              
43              24              19              21             
24              82              58              60             
82              140             58              60             
140             170             30              32             

Total distance (seek): 172 tracks
Average seek distance: 34.40 tracks
Total latency: 182 ms
Average latency per request: 36.40 ms

2 FCFS


#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, st, dist = 0, total_latency = 0;
    const int rotational_latency = 2; // in milliseconds

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &st);

    int curr = st;

    printf("\n%-15s %-15s %-15s %-15s\n", "Current", "Next", "Seek Dist", "Total Latency (ms)");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        int seek = abs(requests[i] - curr);
        int latency = seek + rotational_latency;

        printf("%-15d %-15d %-15d %-15d\n", curr, requests[i], seek, latency);

        dist += seek;
        total_latency += latency;
        curr = requests[i];
    }

    printf("\nTotal distance (seek): %d tracks\n", dist);
    printf("Average seek distance: %.2f tracks\n", (float)dist / n);
    printf("Total latency: %d ms\n", total_latency);
    printf("Average latency per request: %.2f ms\n", (float)total_latency / n);

    return 0;
}

INPUT :

Enter the number of disk requests: 4
Enter the disk requests: 98 183 37 122
Enter the initial head position: 53
