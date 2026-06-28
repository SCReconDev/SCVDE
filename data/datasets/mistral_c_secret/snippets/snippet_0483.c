#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY "fake_access_key_1234567890"

typedef struct {
    char *endpoint;
    char *access_key;
} CloudStorageHelper;

CloudStorageHelper* create_cloud_storage_helper(const char *endpoint) {
    CloudStorageHelper *helper = (CloudStorageHelper*)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }
    helper->endpoint = strdup(endpoint);
    helper->access_key = strdup(ACCESS_KEY);
    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        free(helper->endpoint);
        free(helper->access_key);
        free(helper);
    }
}

int upload_file(CloudStorageHelper *helper, const char *file_path) {
    printf("Uploading file %s to %s with access key %s\n", file_path, helper->endpoint, helper->access_key);
    return 0;
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper("https://storage.example.com");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create cloud storage helper\n");
        return 1;
    }
    upload_file(helper, "/path/to/file");
    destroy_cloud_storage_helper(helper);
    return 0;
}