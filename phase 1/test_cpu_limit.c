#include "types.h"
#include "stat.h"
#include "user.h"

void cpu_intensive_task(int iterations) {
    volatile int i, j;
    for (i = 0; i < iterations; i++) {
        j = i % 10; // Simulate CPU usage
    }
}

int main() {
    printf(1, "=== Testing CPU Limit Implementation ===\n");
    
    printf(1, "Testing CPU limit implementation...\n");
    
    printf(1, "\n--- Task without CPU Limit ---\n");
    int start_time = uptime();
    cpu_intensive_task(1e9);
    int end_time = uptime();
    int base_time = end_time - start_time;
    printf(1, "Task without limit completed in %d ticks\n", base_time);
    
    printf(1, "\n--- Task with 25%% CPU Limit ---\n");
    if (set_limit(25,0) < 0) {
        printf(1, "Failed to set CPU limit\n");
        exit();
    }
    start_time = uptime();
    cpu_intensive_task(1e9);
    end_time = uptime();
    int limited_time1 = end_time - start_time;
    printf(1, "Task with 25%% limit completed in %d ticks\n", limited_time1);

    printf(1, "\n--- Task with 50%% CPU Limit ---\n");
    if (set_limit(50,0) < 0) {
        printf(1, "Failed to set CPU limit\n");
        exit();
    }
    
    start_time = uptime();
    cpu_intensive_task(1e9);
    end_time = uptime();
    int limited_time2 = end_time - start_time;
    
    printf(1, "Task with 50%% limit completed in %d ticks\n", limited_time2);
    
    printf(1, "\n--- Comparison ---\n");
    printf(1, "Base time:    %d ticks\n", base_time);
    printf(1, "25%% Limited time: %d ticks\n", limited_time1);
    printf(1, "50%% Limited time: %d ticks\n", limited_time2);
    
    if (limited_time2 <= base_time * 1.1) {
        printf(1, "CPU limit NOT effectively implemented!\n");
    } else {
        printf(1, "CPU limit appears to be working correctly\n");
    }
    
    exit();
}