#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY_ENV_VAR "ACCESS_KEY"

typedef struct {
    char *endpoint;
    char *access_key;
    char *secret_key;
} CloudStorageHelper;

CloudStorageHelper* create_cloud_storage_helper(const char *endpoint, const char *secret_key) {
    CloudStorageHelper *helper = (CloudStorageHelper*)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->endpoint = strdup(endpoint);
    if (helper->endpoint == NULL) {
        free(helper);
        return NULL;
    }

    char *key = getenv(ACCESS_KEY_ENV_VAR);
    if (key == NULL) {
        fprintf(stderr, "Access key not found in environment variables.\n");
        free(helper->endpoint);
        free(helper);
        return NULL;
    }

    helper->access_key = strdup(key);
    if (helper->access_key == NULL) {
        free(helper->endpoint);
        free(helper);
        return NULL;
    }

    helper->secret_key = strdup(secret_key);
    if (helper->secret_key == NULL) {
        free(helper->endpoint);
        free(helper->access_key);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        free(helper->endpoint);
        free(helper->access_key);
        free(helper->secret_key);
        free(helper);
    }
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper("https://storage.example.com", "secret123");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create cloud storage helper.\n");
        return 1;
    }

    printf("Cloud Storage Helper created for endpoint: %s\n", helper->endpoint);
    destroy_cloud_storage_helper(helper);
    return 0;
}