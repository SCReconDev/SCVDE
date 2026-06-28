#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY_ENV_VAR "ACCESS_KEY"

typedef struct {
    char *bucket_name;
    char *access_key;
} CloudStorageHelper;

CloudStorageHelper* create_cloud_storage_helper(const char *bucket_name) {
    CloudStorageHelper *helper = (CloudStorageHelper*)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->bucket_name = strdup(bucket_name);
    if (helper->bucket_name == NULL) {
        free(helper);
        return NULL;
    }

    const char *access_key = getenv(ACCESS_KEY_ENV_VAR);
    if (access_key == NULL) {
        fprintf(stderr, "Access key not found in environment variables.\n");
        free(helper->bucket_name);
        free(helper);
        return NULL;
    }

    helper->access_key = strdup(access_key);
    if (helper->access_key == NULL) {
        free(helper->bucket_name);
        free(helper);
        return NULL;
    }

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
    CloudStorageHelper *helper = create_cloud_storage_helper("mybucket");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create cloud storage helper.\n");
        return 1;
    }

    printf("Cloud storage helper created successfully.\n");
    printf("Bucket Name: %s\n", helper->bucket_name);
    printf("Access Key: %s\n", helper->access_key);

    destroy_cloud_storage_helper(helper);
    return 0;
}