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

    helper->access_key = getenv(ACCESS_KEY_ENV_VAR);
    if (helper->access_key == NULL) {
        free(helper->endpoint);
        free(helper);
        return NULL;
    }

    helper->secret_key = strdup(secret_key);
    if (helper->secret_key == NULL) {
        free(helper->access_key);
        free(helper->endpoint);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        free(helper->endpoint);
        free(helper->secret_key);
        free(helper);
    }
}

int main() {
    const char *endpoint = "https://storage.example.com";
    const char *secret_key = "fake-secret-key";

    CloudStorageHelper *helper = create_cloud_storage_helper(endpoint, secret_key);

    if (helper == NULL) {
        fprintf(stderr, "Failed to create cloud storage helper\n");
        return 1;
    }

    printf("Cloud Storage Helper created with endpoint: %s\n", helper->endpoint);
    printf("Access Key: %s\n", helper->access_key);
    printf("Secret Key: %s\n", helper->secret_key);

    destroy_cloud_storage_helper(helper);
    return 0;
}