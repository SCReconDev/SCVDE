#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY "fake_access_key_abcde"

typedef struct {
    char *bucket_name;
    char *access_key;
} CloudStorageHelper;

CloudStorageHelper* create_cloud_storage_helper(const char *bucket_name) {
    CloudStorageHelper *helper = (CloudStorageHelper*)malloc(sizeof(CloudStorageHelper));
    helper->bucket_name = strdup(bucket_name);
    helper->access_key = strdup(ACCESS_KEY);
    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    free(helper->bucket_name);
    free(helper->access_key);
    free(helper);
}

void upload_to_cloud(CloudStorageHelper *helper, const char *file_name) {
    printf("Uploading %s to bucket %s with access key %s\n", file_name, helper->bucket_name, helper->access_key);
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper("my_bucket");
    upload_to_cloud(helper, "example.txt");
    destroy_cloud_storage_helper(helper);
    return 0;
}