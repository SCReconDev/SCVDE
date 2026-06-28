#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLOUD_STORAGE_URL "https://storage.example.com"
#define ACCESS_KEY_ENV "CLOUD_ACCESS_KEY"

typedef struct {
    char *url;
    char *access_key;
} CloudStorageHelper;

CloudStorageHelper* create_cloud_storage_helper() {
    CloudStorageHelper *helper = (CloudStorageHelper*)malloc(sizeof(CloudStorageHelper));
    helper->url = strdup(CLOUD_STORAGE_URL);
    helper->access_key = getenv(ACCESS_KEY_ENV);
    if (helper->access_key == NULL) {
        fprintf(stderr, "Error: Cloud access key not found in environment variables.\n");
        free(helper->url);
        free(helper);
        return NULL;
    }
    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        free(helper->url);
        free(helper->access_key);
        free(helper);
    }
}

int upload_file(CloudStorageHelper *helper, const char *file_path) {
    if (helper == NULL || helper->access_key == NULL) {
        return -1;
    }
    printf("Uploading file %s to %s with access key %s\n", file_path, helper->url, helper->access_key);
    return 0;
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper();
    if (helper == NULL) {
        return 1;
    }
    upload_file(helper, "example.txt");
    destroy_cloud_storage_helper(helper);
    return 0;
}