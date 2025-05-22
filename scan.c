1 scan 

#include <stdio.h>
#include <stdlib.h>

void scan(int requests[], int n, int head, int disk_size) {
    int left[n], right[n];
    int left_count = 0, right_count = 0;
    int total_distance = 0, total_latency = 0;
    const int rotational_latency = 2;

    // Separate into left and right of head
    for (int i = 0; i < n; i++) {
        if (requests[i] < head)
            left[left_count++] = requests[i];
        else
            right[right_count++] = requests[i];
    }

    // Sort left in descending order
    for (int i = 0; i < left_count - 1; i++) {
        for (int j = i + 1; j < left_count; j++) {
            if (left[i] < left[j]) {
                int tmp = left[i];
                left[i] = left[j];
                left[j] = tmp;
            }
        }
    }

    // Sort right in ascending order
    for (int i = 0; i < right_count - 1; i++) {
        for (int j = i + 1; j < right_count; j++) {
            if (right[i] > right[j]) {
                int tmp = right[i];
                right[i] = right[j];
                right[j] = tmp;
            }
        }
    }

    printf("\nDisk Scheduling Order (SCAN):\n");
    printf("%-10s %-10s %-15s %-15s\n", "Current", "Next", "Seek Distance", "Latency (ms)");
    printf("---------------------------------------------------------\n");

    int curr = head;

    // Move towards higher track numbers (right direction)
    for (int i = 0; i < right_count; i++) {
        int dist = abs(curr - right[i]);
        int latency = dist + rotational_latency;
        printf("%-10d %-10d %-15d %-15d\n", curr, right[i], dist, latency);
        total_distance += dist;
        total_latency += latency;
        curr = right[i];
    }

    // Go to the end (if not already)
    if (curr != disk_size - 1) {
        total_distance += abs(curr - (disk_size - 1));
        curr = disk_size - 1;
    }

    // Then move to left side
    for (int i = 0; i < left_count; i++) {
        int dist = abs(curr - left[i]);
        int latency = dist + rotational_latency;
        printf("%-10d %-10d %-15d %-15d\n", curr, left[i], dist, latency);
        total_distance += dist;
        total_latency += latency;
        curr = left[i];
    }

    printf("\nTotal Seek Distance: %d tracks\n", total_distance);
    printf("Average Seek Distance: %.2f tracks\n", (float)total_distance / n);
    printf("Total Latency: %d ms\n", total_latency);
    printf("Average Latency: %.2f ms\n", (float)total_latency / n);
}

int main() {
    int n, head, disk_size;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the disk size (e.g., 200 for 0-199): ");
    scanf("%d", &disk_size);

    scan(requests, n, head, disk_size);

    return 0;
}

OUTPUT

Enter the number of disk requests: 7
Enter the disk requests: 82 170 43 140 24 16 190
Enter the initial head position: 50
Enter the disk size (e.g., 200 for 0-199): 200

Disk Scheduling Order (SCAN):
Current    Next       Seek Distance   Latency (ms)   
---------------------------------------------------------
50         82         32              34             
82         140        58              60             
140        170        30              32             
170        190        20              22             
199        43         156             158            
43         24         19              21             
24         16         8               10             

Total Seek Distance: 332 tracks
Average Seek Distance: 47.43 tracks
Total Latency: 337 ms
Average Latency: 48.14 ms


ORR

#include <stdio.h> 
#include <stdlib.h> 
 
void scan(int requests[], int n, int st, int disk_size) { 
    int left = 0, right = 0; 
    int distance = 0; 
    int total_distance = 0; 
 
    int left_arr[n], right_arr[n]; 
    int left_index = 0, right_index = 0; 
 
    // Separate the requests into left and right of the initial head position 
    for (int i = 0; i < n; i++) { 
        if (requests[i] < st) { 
            left_arr[left_index++] = requests[i]; 
        } else { 
            right_arr[right_index++] = requests[i]; 
        } 
    } 
 
    // Sort the left and right arrays 
    for (int i = 0; i < left_index - 1; i++) { 
        for (int j = i + 1; j < left_index; j++) { 
            if (left_arr[i] < left_arr[j]) { 
                int temp = left_arr[i]; 
                left_arr[i] = left_arr[j]; 
                left_arr[j] = temp; 
            } 
        } 
    } 
     
    for (int i = 0; i < right_index - 1; i++) { 
        for (int j = i + 1; j < right_index; j++) { 
            if (right_arr[i] > right_arr[j]) { 
                int temp = right_arr[i]; 
                right_arr[i] = right_arr[j]; 
                right_arr[j] = temp; 
            } 
        } 
    } 
 
    // Total distance calculation 
    // Traverse the right side of the head 
    total_distance += abs(st - right_arr[0]); 
    distance = total_distance; 
    for (int i = 0; i < right_index; i++) { 
        printf("%d -> ", right_arr[i]); 
        if (i == right_index - 1) { 
            total_distance += abs(right_arr[i] - disk_size); 
            distance = total_distance; 
        } else { 
            total_distance += abs(right_arr[i] - right_arr[i + 1]); 
        } 
    } 
     
    // Now reverse and traverse the left side of the head 
    total_distance += abs(disk_size - left_arr[0]); 
    for (int i = 0; i < left_index; i++) { 
        printf("%d -> ", left_arr[i]); 
        if (i == left_index - 1) { 
            total_distance += abs(left_arr[i] - 0); 
            distance = total_distance; 
        } else { 
            total_distance += abs(left_arr[i] - left_arr[i + 1]); 
        } 
    } 
     
    printf("\nTotal distance: %d\n", total_distance); 
    printf("Average Seek Distance: %.2f\n", (float)total_distance / n); 
} 
 
int main() { 
    int n, st, disk_size; 
 
    // Input the number of requests, initial head position, and disk size 
    printf("Enter the number of disk requests: "); 
    scanf("%d", &n); 
 
    int requests[n]; 
    printf("Enter the disk requests: "); 
    for (int i = 0; i < n; i++) { 
        scanf("%d", &requests[i]); 
    } 
printf("Enter the initial head position: "); 
scanf("%d", &st); 
printf("Enter the disk size: "); 
scanf("%d", &disk_size); 
// Call SCAN function 
scan(requests, n, st, disk_size); 
return 0; 
} 