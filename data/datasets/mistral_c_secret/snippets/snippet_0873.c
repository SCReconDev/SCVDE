#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCESS_KEY_LENGTH 100

char* get_access_key() {
    char* access_key = getenv("CLOUD_ACCESS_KEY");
    if (access_key == NULL) {
        fprintf(stderr, "CLOUD_ACCESS_KEY environment variable not set.\n");
        exit(EXIT_FAILURE);
    }
    return strdup(access_key);
}

void upload_to_cloud(char* access_key) {
    printf("Uploading to cloud storage with access key: %s\n", access_key);
    // Simulate cloud upload
}

int main() {
    char* access_key = get_access_key();
    upload_to_cloud(access_key);
    free(access_key);
    return 0;
}