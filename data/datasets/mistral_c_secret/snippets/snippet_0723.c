#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *access_key;
    char *secret_key;
    char *endpoint;
} CloudStorageHelper;

CloudStorageHelper* create_cloud_storage_helper() {
    CloudStorageHelper *helper = (CloudStorageHelper*)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->access_key = getenv("CLOUD_ACCESS_KEY");
    if (helper->access_key == NULL) {
        fprintf(stderr, "CLOUD_ACCESS_KEY environment variable not set.\n");
        free(helper);
        return NULL;
    }

    helper->secret_key = getenv("CLOUD_SECRET_KEY");
    if (helper->secret_key == NULL) {
        fprintf(stderr, "CLOUD_SECRET_KEY environment variable not set.\n");
        free(helper);
        return NULL;
    }

    helper->endpoint = getenv("CLOUD_ENDPOINT");
    if (helper->endpoint == NULL) {
        fprintf(stderr, "CLOUD_ENDPOINT environment variable not set.\n");
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        free(helper);
    }
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper();
    if (helper == NULL) {
        return EXIT_FAILURE;
    }

    printf("Cloud Storage Helper created successfully.\n");
    printf("Access Key: %s\n", helper->access_key);
    printf("Endpoint: %s\n", helper->endpoint);

    destroy_cloud_storage_helper(helper);
    return EXIT_SUCCESS;
}