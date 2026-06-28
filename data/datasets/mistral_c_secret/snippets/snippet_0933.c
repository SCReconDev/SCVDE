#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY_ENV_VAR "ACCESS_KEY"

typedef struct {
    char *endpoint;
    char *access_key;
    char *bucket;
} CloudStorageHelper;

CloudStorageHelper* create_cloud_storage_helper(const char *endpoint, const char *bucket) {
    CloudStorageHelper *helper = (CloudStorageHelper *)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->endpoint = strdup(endpoint);
    if (helper->endpoint == NULL) {
        free(helper);
        return NULL;
    }

    helper->access_key = getenv(ACCESS_KEY_ENV_VAR);
    if (helper->access_key == NULL) {
        fprintf(stderr, "Error: Access key not found in environment variables.\n");
        free(helper->endpoint);
        free(helper);
        return NULL;
    }

    helper->bucket = strdup(bucket);
    if (helper->bucket == NULL) {
        free(helper->endpoint);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        free(helper->endpoint);
        free(helper->bucket);
        free(helper);
    }
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper("https://storage.example.com", "mybucket");
    if (helper == NULL) {
        return 1;
    }

    printf("Cloud Storage Helper created successfully.\n");
    printf("Endpoint: %s\n", helper->endpoint);
    printf("Access Key: %s\n", helper->access_key);
    printf("Bucket: %s\n", helper->bucket);

    destroy_cloud_storage_helper(helper);
    return 0;
}