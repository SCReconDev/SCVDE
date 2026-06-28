#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY "fake_access_key_1234567890"

typedef struct {
    char *storage_url;
    char *access_key;
} CloudStorageHelper;

CloudStorageHelper *create_cloud_storage_helper(const char *url) {
    CloudStorageHelper *helper = (CloudStorageHelper *)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->storage_url = strdup(url);
    helper->access_key = strdup(ACCESS_KEY);

    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        free(helper->storage_url);
        free(helper->access_key);
        free(helper);
    }
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper("https://storage.example.com");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create cloud storage helper\n");
        return 1;
    }

    printf("Cloud Storage Helper created with URL: %s\n", helper->storage_url);
    printf("Access Key: %s\n", helper->access_key);

    destroy_cloud_storage_helper(helper);
    return 0;
}