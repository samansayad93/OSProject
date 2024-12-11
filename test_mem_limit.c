#include "types.h"
#include "stat.h"
#include "user.h"

int main(){
    if (set_limit(100,1024) < 0) {
        printf(1, "Failed to set CPU limit\n");
        exit();
    }
    exit();
}