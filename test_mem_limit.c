// #include "types.h"
// #include "stat.h"
// #include "user.h"

// #define ALLOC_SIZE 1024
// #define NUM_ALLOCS 100

// int main() {
//     printf(1, "=== Memory Limit Test ===\n");
    
//     // Set memory limit (e.g., 1MB = 1024 * 1024 bytes)
//     int limit = 50 * 1024;
//     if (set_limit(100,limit) < 0) {
//         printf(1, "Failed to set memory limit\n");
//         exit();
//     }
    
//     printf(1, "Memory limit set to %d bytes\n", limit);
    
//     // Try to allocate memory
//     void* allocations[NUM_ALLOCS];
//     int successful_allocs = 0;
    
//     printf(1, "Attempting to allocate memory...\n");
    
//     for (int i = 0; i < NUM_ALLOCS; i++) {
//         allocations[i] = malloc(ALLOC_SIZE);
        
//         if (allocations[i] == 0) {
//             printf(1, "Allocation failed at %d attempts\n", i);
//             break;
//         }
        
//         successful_allocs++;
//     }
    
//     printf(1, "Successfully allocated %d blocks\n", successful_allocs);
    
//     // Free allocated memory
//     for (int i = 0; i < successful_allocs; i++) {
//         free(allocations[i]);
//     }
    
//     printf(1, "Memory freed\n");
    
//     exit();
// }



/// this is changed

// #include "types.h"
// #include "stat.h"
// #include "user.h"

// int main() {
//     printf(1, "Memory Allocation Test\n");

//     // Set memory limit for the process
//     int limit = 1024; // Limit in bytes
//     printf(1, "Setting memory limit to %d bytes...\n", limit);
//     if (set_limit(100,limit) < 0) {
//         printf(1, "Error: Failed to set memory limit.\n");
//         exit();
//     }

//     // Attempt to allocate within the limit
//     int alloc_size = 512;
//     printf(1, "Allocating %d bytes...\n", alloc_size);
//     void *mem1 = malloc(alloc_size);
//     if (mem1 == 0) {
//         printf(1, "Allocation failed for %d bytes.\n", alloc_size);
//     } else {
//         printf(1, "Allocation succeeded for %d bytes.\n", alloc_size);
//     }

//     // Attempt to allocate beyond the limit
//     alloc_size = 600;
//     printf(1, "Allocating %d bytes...\n", alloc_size);
//     void *mem2 = malloc(alloc_size);
//     if (mem2 == 0) {
//         printf(1, "Allocation failed for %d bytes as expected.\n", alloc_size);
//     } else {
//         printf(1, "Allocation succeeded for %d bytes unexpectedly.\n", alloc_size);
//     }

//     // Free the first allocation
//     printf(1, "Freeing first allocation...\n");
//     free(mem1);

//     // Attempt to allocate again within the freed space
//     alloc_size = 256;
//     printf(1, "Allocating %d bytes...\n", alloc_size);
//     void *mem3 = malloc(alloc_size);
//     if (mem3 == 0) {
//         printf(1, "Allocation failed for %d bytes.\n", alloc_size);
//     } else {
//         printf(1, "Allocation succeeded for %d bytes.\n", alloc_size);
//     }

//     printf(1, "Memory Allocation Test Completed.\n");
//     exit();
// }


#include "types.h"
#include "stat.h"
#include "user.h"

int main(){
    if (set_limit(100,512) < 0) {
        printf(1, "Error: Failed to set memory limit.\n");
        exit();
    }
    if(sys_check_memory_allocation(1024)){
        printf(1,"success\n");
    };
    exit();
}