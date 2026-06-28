#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY "fake_access_key_1234567890"

typedef struct {
    char *bucket_name;
    char *access_key;
} CloudStorageHelper;

CloudStorageHelper *create_cloud_storage_helper(const char *bucket_name) {
    CloudStorageHelper *helper = (CloudStorageHelper *)malloc(sizeof(CloudStorageHelper));
    helper->bucket_name = strdup(bucket_name);
    helper->access_key = strdup(ACCESS_KEY);
    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    free(helper->bucket_name);
    free(helper->access_key);
    free(helper);
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper("example-bucket");
    printf("Cloud Storage Helper created with access key: %s\n", helper->access_key);
    destroy_cloud_storage_helper(helper);
    return 0;
}