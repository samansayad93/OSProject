#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    printf(1, "Memory Allocation Test\n");
    int alloc_size = 512;
    void *mem0 = malloc(alloc_size);
    if (mem0 == 0) {
        printf(1, "Allocation failed for %d bytes.\n", alloc_size);
    } else {
        printf(1, "Allocation succeeded for %d bytes.\n", alloc_size);
    }
    // Set memory limit for the process
    int limit = 1024; // Limit in bytes
    printf(1, "Setting memory limit to %d bytes...\n", limit);
    if (set_limit(100,limit) < 0) {
        printf(1, "Error: Failed to set memory limit.\n");
        exit();
    }
    // Attempt to allocate within the limit
    printf(1, "Allocating %d bytes...\n", alloc_size);
    void *mem1 = malloc(alloc_size);
    if (mem1 == 0) {
        printf(1, "Allocation failed for %d bytes.\n", alloc_size);
    } else {
        printf(1, "Allocation succeeded for %d bytes.\n", alloc_size);
    }
    // Attempt to allocate beyond the limit
    alloc_size = 600;
    printf(1, "Allocating %d bytes...\n", alloc_size);
    void *mem2 = malloc(alloc_size);
    if (mem2 == 0) {
        printf(1, "Allocation failed for %d bytes as expected.\n", alloc_size);
    } else {
        printf(1, "Allocation succeeded for %d bytes unexpectedly.\n", alloc_size);
    }
    // Free the first allocation
    printf(1, "Freeing first allocation...\n");
    free(mem1);
    // Attempt to allocate again within the freed space
    alloc_size = 256;
    printf(1, "Allocating %d bytes...\n", alloc_size);
    void *mem3 = malloc(alloc_size);
    if (mem3 == 0) {
        printf(1, "Allocation failed for %d bytes.\n", alloc_size);
    } else {
        printf(1, "Allocation succeeded for %d bytes.\n", alloc_size);
    }
    printf(1, "Memory Allocation Test Completed.\n");
    exit();
}