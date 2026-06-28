#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY "fake_access_key_1234567890"

typedef struct {
    char *bucket_name;
    char *access_key;
} CloudStorageHelper;

CloudStorageHelper *create_cloud_storage_helper(const char *bucket_name) {
    CloudStorageHelper *helper = (CloudStorageHelper *)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }
    helper->bucket_name = strdup(bucket_name);
    helper->access_key = strdup(ACCESS_KEY);
    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        free(helper->bucket_name);
        free(helper->access_key);
        free(helper);
    }
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper("my-bucket");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create cloud storage helper\n");
        return 1;
    }

    printf("Cloud Storage Helper created with access key: %s\n", helper->access_key);

    destroy_cloud_storage_helper(helper);
    return 0;
}