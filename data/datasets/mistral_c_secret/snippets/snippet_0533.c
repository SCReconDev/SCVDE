#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STORAGE_URL "https://storage.example.com/v1"
#define ACCESS_KEY_ENV_VAR "STORAGE_ACCESS_KEY"

typedef struct {
    char *access_key;
    char *url;
} StorageHelper;

StorageHelper* create_helper() {
    StorageHelper *helper = (StorageHelper*)malloc(sizeof(StorageHelper));
    helper->url = strdup(STORAGE_URL);
    helper->access_key = getenv(ACCESS_KEY_ENV_VAR);
    if (helper->access_key == NULL) {
        fprintf(stderr, "Error: Access key not found in environment variables.\n");
        free(helper->url);
        free(helper);
        return NULL;
    }
    return helper;
}

void destroy_helper(StorageHelper *helper) {
    if (helper != NULL) {
        free(helper->url);
        free(helper);
    }
}

int upload_file(StorageHelper *helper, const char *file_path) {
    if (helper == NULL || helper->access_key == NULL || file_path == NULL) {
        return -1;
    }
    printf("Uploading file %s to %s with access key: %s\n", file_path, helper->url, helper->access_key);
    return 0;
}

int main() {
    StorageHelper *helper = create_helper();
    if (helper == NULL) {
        return EXIT_FAILURE;
    }
    upload_file(helper, "/path/to/file.txt");
    destroy_helper(helper);
    return EXIT_SUCCESS;
}