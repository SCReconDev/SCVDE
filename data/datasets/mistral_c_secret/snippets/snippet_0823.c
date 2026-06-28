#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLOUD_STORAGE_URL "https://storage.example.com/v1"
#define ACCESS_KEY_ENV_VAR "ACCESS_KEY"

typedef struct {
    char* url;
    char* access_key;
} CloudStorageHelper;

CloudStorageHelper* create_cloud_storage_helper() {
    CloudStorageHelper* helper = (CloudStorageHelper*)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->url = strdup(CLOUD_STORAGE_URL);
    if (helper->url == NULL) {
        free(helper);
        return NULL;
    }

    helper->access_key = getenv(ACCESS_KEY_ENV_VAR);
    if (helper->access_key == NULL) {
        free(helper->url);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper* helper) {
    if (helper != NULL) {
        free(helper->url);
        free(helper->access_key);
        free(helper);
    }
}

int main() {
    CloudStorageHelper* helper = create_cloud_storage_helper();
    if (helper == NULL) {
        fprintf(stderr, "Failed to create cloud storage helper\n");
        return 1;
    }

    printf("Cloud Storage Helper created successfully\n");
    printf("URL: %s\n", helper->url);
    printf("Access Key: %s\n", helper->access_key);

    destroy_cloud_storage_helper(helper);
    return 0;
}