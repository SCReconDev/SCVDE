#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY "fake_access_key_1234567890"
#define SECRET_KEY "fake_secret_key_0987654321"

typedef struct {
    char *bucket_name;
    char *access_key;
    char *secret_key;
} CloudStorageHelper;

CloudStorageHelper *create_cloud_storage_helper(const char *bucket_name) {
    CloudStorageHelper *helper = (CloudStorageHelper *)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->bucket_name = strdup(bucket_name);
    if (helper->bucket_name == NULL) {
        free(helper);
        return NULL;
    }

    helper->access_key = strdup(ACCESS_KEY);
    if (helper->access_key == NULL) {
        free(helper->bucket_name);
        free(helper);
        return NULL;
    }

    helper->secret_key = strdup(SECRET_KEY);
    if (helper->secret_key == NULL) {
        free(helper->bucket_name);
        free(helper->access_key);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        free(helper->bucket_name);
        free(helper->access_key);
        free(helper->secret_key);
        free(helper);
    }
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper("example-bucket");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create cloud storage helper\n");
        return EXIT_FAILURE;
    }

    printf("Cloud storage helper created with bucket name: %s\n", helper->bucket_name);
    printf("Access key: %s\n", helper->access_key);
    printf("Secret key: %s\n", helper->secret_key);

    destroy_cloud_storage_helper(helper);
    return EXIT_SUCCESS;
}