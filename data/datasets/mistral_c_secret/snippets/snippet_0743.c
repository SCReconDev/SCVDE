#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *access_key;
    char *secret_key;
    char *bucket_name;
} CloudStorageHelper;

CloudStorageHelper* create_cloud_storage_helper(const char *access_key, const char *secret_key) {
    CloudStorageHelper *helper = (CloudStorageHelper*)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->access_key = strdup(access_key);
    if (helper->access_key == NULL) {
        free(helper);
        return NULL;
    }

    helper->secret_key = strdup(secret_key);
    if (helper->secret_key == NULL) {
        free(helper->access_key);
        free(helper);
        return NULL;
    }

    helper->bucket_name = strdup("my-bucket");
    if (helper->bucket_name == NULL) {
        free(helper->secret_key);
        free(helper->access_key);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        free(helper->bucket_name);
        free(helper->secret_key);
        free(helper->access_key);
        free(helper);
    }
}

int main() {
    const char *access_key = getenv("AWS_ACCESS_KEY_ID");
    const char *secret_key = getenv("AWS_SECRET_ACCESS_KEY");

    if (access_key == NULL || secret_key == NULL) {
        fprintf(stderr, "AWS_ACCESS_KEY_ID or AWS_SECRET_ACCESS_KEY environment variable not set\n");
        return 1;
    }

    CloudStorageHelper *helper = create_cloud_storage_helper(access_key, secret_key);
    if (helper == NULL) {
        fprintf(stderr, "Failed to create cloud storage helper\n");
        return 1;
    }

    printf("Cloud Storage Helper created with access key: %s\n", helper->access_key);
    printf("Bucket name: %s\n", helper->bucket_name);

    destroy_cloud_storage_helper(helper);

    return 0;
}