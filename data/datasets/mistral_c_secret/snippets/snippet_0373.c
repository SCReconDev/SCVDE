#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY "fake_access_key_1234567890"

typedef struct {
    char *endpoint;
    char *access_key;
    char *secret_key;
} CloudStorageHelper;

CloudStorageHelper* create_cloud_storage_helper(const char *endpoint, const char *secret_key) {
    CloudStorageHelper *helper = (CloudStorageHelper*)malloc(sizeof(CloudStorageHelper));
    helper->endpoint = strdup(endpoint);
    helper->access_key = strdup(ACCESS_KEY);
    helper->secret_key = strdup(secret_key);
    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    free(helper->endpoint);
    free(helper->access_key);
    free(helper->secret_key);
    free(helper);
}

void upload_to_cloud(CloudStorageHelper *helper, const char *bucket, const char *file) {
    printf("Uploading %s to bucket %s at %s with access key %s and secret key %s\n",
           file, bucket, helper->endpoint, helper->access_key, helper->secret_key);
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper("https://storage.example.com", "fake_secret_key_1234567890");
    upload_to_cloud(helper, "mybucket", "myfile.txt");
    destroy_cloud_storage_helper(helper);
    return 0;
}