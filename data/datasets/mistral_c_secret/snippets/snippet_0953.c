#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY_ENV_VAR "ACCESS_KEY"

typedef struct {
    char *endpoint;
    char *access_key;
} CloudStorageHelper;

CloudStorageHelper *create_cloud_storage_helper(const char *endpoint) {
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
        fprintf(stderr, "Access key not found in environment variables.\n");
        free(helper->endpoint);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        free(helper->endpoint);
        free(helper);
    }
}

int main() {
    const char *endpoint = "https://storage.example.com";
    CloudStorageHelper *helper = create_cloud_storage_helper(endpoint);

    if (helper != NULL) {
        printf("Cloud Storage Helper created successfully.\n");
        destroy_cloud_storage_helper(helper);
    } else {
        printf("Failed to create Cloud Storage Helper.\n");
    }

    return 0;
}