#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLOUD_STORAGE_ACCESS_KEY_ENV_VAR "CLOUD_STORAGE_ACCESS_KEY"
#define CLOUD_STORAGE_SECRET_KEY_ENV_VAR "CLOUD_STORAGE_SECRET_KEY"

typedef struct {
    char *access_key;
    char *secret_key;
} CloudStorageHelper;

CloudStorageHelper *create_cloud_storage_helper() {
    CloudStorageHelper *helper = (CloudStorageHelper *)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    char *access_key = getenv(CLOUD_STORAGE_ACCESS_KEY_ENV_VAR);
    char *secret_key = getenv(CLOUD_STORAGE_SECRET_KEY_ENV_VAR);

    if (access_key == NULL || secret_key == NULL) {
        fprintf(stderr, "Error: Cloud storage credentials not found in environment variables.\n");
        free(helper);
        return NULL;
    }

    helper->access_key = strdup(access_key);
    helper->secret_key = strdup(secret_key);

    if (helper->access_key == NULL || helper->secret_key == NULL) {
        free(helper->access_key);
        free(helper->secret_key);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        free(helper->access_key);
        free(helper->secret_key);
        free(helper);
    }
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper();
    if (helper == NULL) {
        return 1;
    }

    printf("Cloud Storage Helper created successfully.\n");
    printf("Access Key: %s\n", helper->access_key);
    printf("Secret Key: %s\n", helper->secret_key);

    destroy_cloud_storage_helper(helper);
    return 0;
}