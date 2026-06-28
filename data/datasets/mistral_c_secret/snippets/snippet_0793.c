#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    CURL *curl;
    char *access_key;
    char *secret_key;
    char *bucket;
} CloudStorageHelper;

CloudStorageHelper *create_cloud_storage_helper(const char *bucket) {
    CloudStorageHelper *helper = malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->bucket = strdup(bucket);
    if (helper->bucket == NULL) {
        free(helper);
        return NULL;
    }

    helper->access_key = getenv("CLOUD_ACCESS_KEY");
    helper->secret_key = getenv("CLOUD_SECRET_KEY");

    if (helper->access_key == NULL || helper->secret_key == NULL) {
        fprintf(stderr, "CLOUD_ACCESS_KEY or CLOUD_SECRET_KEY environment variable not set\n");
        free(helper->bucket);
        free(helper);
        return NULL;
    }

    helper->curl = curl_easy_init();
    if (helper->curl == NULL) {
        fprintf(stderr, "curl_easy_init() failed\n");
        free(helper->bucket);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        curl_easy_cleanup(helper->curl);
        free(helper->bucket);
        free(helper);
    }
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper("my-bucket");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create cloud storage helper\n");
        return 1;
    }

    printf("Cloud storage helper created for bucket: %s\n", helper->bucket);
    printf("Access key: %s\n", helper->access_key);

    destroy_cloud_storage_helper(helper);
    return 0;
}