#include "types.h"
#include "stat.h"
#include "user.h"

// Workload function to simulate computation and allow testing of preemption
void workload(int id) {
    for (int i = 0; i < 100000000; i++) {
        if (i % 10000000 == 0) {
            printf(1, "Process %d is running, iteration %d\n", id, i / 10000000);
        }
    }
    printf(1, "Process %d completed\n", id);
    exit();
}


int main(void) {
    int p1, p2;

    printf(1, "Starting test for priority scheduling and time slice\n");

    // Fork process 1: Low priority
    if ((p1 = fork()) == 0) {
        printf(1, "Process 1 (Low Priority) started\n");
        setpriority(getpid(), 5);  // Set low priority
        workload(1);
    }

    // Fork process 2: High priority
    if ((p2 = fork()) == 0) {
        printf(1, "Process 2 (High Priority) started\n");
        setpriority(getpid(), 15);  // Set high priority
        workload(2);
    }



    // Parent process waits for all child processes to complete
    while (wait() > 0);

    printf(1, "All processes completed\n");
    exit();
}
