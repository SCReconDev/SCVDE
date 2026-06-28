#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLOUD_ACCESS_KEY_ENV_VAR "CLOUD_ACCESS_KEY"

char* get_cloud_access_key() {
    char* access_key = getenv(CLOUD_ACCESS_KEY_ENV_VAR);
    if (access_key == NULL) {
        fprintf(stderr, "Error: Cloud access key not found in environment variables.\n");
        exit(EXIT_FAILURE);
    }
    return access_key;
}

void upload_to_cloud_storage() {
    char* access_key = get_cloud_access_key();
    printf("Uploading to cloud storage with access key: %s\n", access_key);
    // Simulate cloud storage upload
}

int main() {
    upload_to_cloud_storage();
    return 0;
}