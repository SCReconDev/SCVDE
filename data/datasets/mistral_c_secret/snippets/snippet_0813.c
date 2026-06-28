#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    CURL *curl;
    char *access_key;
    char *bucket_name;
} CloudStorageHelper;

CloudStorageHelper* create_cloud_storage_helper(const char *bucket_name) {
    CloudStorageHelper *helper = (CloudStorageHelper*)malloc(sizeof(CloudStorageHelper));
    helper->bucket_name = strdup(bucket_name);
    helper->access_key = getenv("CLOUD_ACCESS_KEY");
    if (helper->access_key == NULL) {
        fprintf(stderr, "CLOUD_ACCESS_KEY environment variable not set\n");
        free(helper->bucket_name);
        free(helper);
        return NULL;
    }
    helper->curl = curl_easy_init();
    if (helper->curl == NULL) {
        fprintf(stderr, "Failed to initialize CURL\n");
        free(helper->bucket_name);
        free(helper);
        return NULL;
    }
    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        curl_easy_cleanup(helper->curl);
        free(helper->bucket_name);
        free(helper);
    }
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper("my-bucket");
    if (helper == NULL) {
        return 1;
    }
    printf("Cloud storage helper created for bucket: %s\n", helper->bucket_name);
    destroy_cloud_storage_helper(helper);
    return 0;
}