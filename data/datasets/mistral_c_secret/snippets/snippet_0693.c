#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *access_key;
    char *secret_key;
    char *bucket_name;
} CloudStorageHelper;

CloudStorageHelper *create_cloud_storage_helper(const char *bucket_name) {
    CloudStorageHelper *helper = malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->bucket_name = strdup(bucket_name);
    if (helper->bucket_name == NULL) {
        free(helper);
        return NULL;
    }

    helper->access_key = getenv("CLOUD_ACCESS_KEY");
    if (helper->access_key == NULL) {
        free(helper->bucket_name);
        free(helper);
        return NULL;
    }

    helper->secret_key = getenv("CLOUD_SECRET_KEY");
    if (helper->secret_key == NULL) {
        free(helper->access_key);
        free(helper->bucket_name);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        if (helper->bucket_name != NULL) {
            free(helper->bucket_name);
        }
        free(helper);
    }
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper("my-bucket");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create Cloud Storage Helper\n");
        return 1;
    }

    printf("Cloud Storage Helper created with access key: %s\n", helper->access_key);

    destroy_cloud_storage_helper(helper);
    return 0;
}