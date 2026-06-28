#include <stdio.h>
#include <stdlib.h>

void cleanup_resource(void** resource) {
    if (*resource != NULL) {
        free(*resource);
        *resource = NULL;
    }
}

int main() {
    void* resource = malloc(100);
    cleanup_resource(&resource);
    return 0;
}