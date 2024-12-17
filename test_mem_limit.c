#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    printf(1, "Memory Allocation Test\n");
    int alloc_size = 128;
    void *mem0 = malloc(alloc_size);
    if (mem0 == 0) {
        printf(1, "Allocation failed for %d bytes.\n", alloc_size);
    } else {
        printf(1, "Allocation succeeded for %d bytes.\n", alloc_size);
    }

    int limit = 1024;
    printf(1, "Setting memory limit to %d bytes...\n", limit);
    if (set_limit(100,limit) < 0) {
        printf(1, "Error: Failed to set memory limit.\n");
        exit();
    }

    alloc_size =512;
    printf(1, "Allocating %d bytes...\n", alloc_size);
    void *mem1 = malloc(alloc_size);
    if (mem1 == 0) {
        printf(1, "Allocation failed for %d bytes.\n", alloc_size);
    } else {
        printf(1, "Allocation succeeded for %d bytes.\n", alloc_size);
    }
    alloc_size = 600;
    printf(1, "Allocating %d bytes...\n", alloc_size);
    void *mem2 = malloc(alloc_size);
    if (mem2 == 0) {
        printf(1, "Allocation failed for %d bytes.\n", alloc_size);
    } else {
        printf(1, "Allocation succeeded for %d bytes.\n", alloc_size);
    }

    printf(1, "Freeing mem1 allocation...\n");
    free(mem1);

    alloc_size = 256;
    printf(1, "Allocating %d bytes...\n", alloc_size);
    void *mem3 = malloc(alloc_size);
    if (mem3 == 0) {
        printf(1, "Allocation failed for %d bytes.\n", alloc_size);
    } else {
        printf(1, "Allocation succeeded for %d bytes.\n", alloc_size);
    }

    limit = 512;
    printf(1, "Setting memory limit to %d bytes...\n", limit);
    if(set_limit(100,limit) < 0){
        printf(1, "Error: Failed to set memory limit.\n");
        exit();
    }

    alloc_size = 128;
    printf(1, "Allocating %d bytes...\n", alloc_size);
    void *mem4 = malloc(alloc_size);
    if (mem4 == 0) {
        printf(1, "Allocation failed for %d bytes.\n", alloc_size);
    } else {
        printf(1, "Allocation succeeded for %d bytes.\n", alloc_size);
    }

    printf(1, "Freeing mem3 allocation...\n");
    free(mem3);

    alloc_size = 128;
    printf(1, "Allocating %d bytes...\n", alloc_size);
    void *mem5 = malloc(alloc_size);
    if (mem5 == 0) {
        printf(1, "Allocation failed for %d bytes.\n", alloc_size);
    } else {
        printf(1, "Allocation succeeded for %d bytes.\n", alloc_size);
    }

    printf(1, "Memory Allocation Test Completed.\n");
    exit();
}