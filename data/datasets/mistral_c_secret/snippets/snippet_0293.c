#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY "AKIAIOSFODNN7EXAMPLE"

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
    helper->access_key = strdup(ACCESS_KEY);
    helper->secret_key = strdup(secret_key);

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
    CloudStorageHelper *helper = create_cloud_storage_helper("https://storage.example.com", "wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create cloud storage helper\n");
        return 1;
    }

    printf("Cloud Storage Helper created with access key: %s\n", helper->access_key);

    destroy_cloud_storage_helper(helper);
    return 0;
}