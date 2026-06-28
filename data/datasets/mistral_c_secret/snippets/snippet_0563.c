#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define ACCESS_KEY_ENV_VAR "ACCESS_KEY"

typedef struct {
    CURL *curl;
    char *access_key;
    char *bucket_name;
} CloudStorageHelper;

CloudStorageHelper *create_cloud_storage_helper(const char *bucket_name) {
    CloudStorageHelper *helper = (CloudStorageHelper *)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->bucket_name = strdup(bucket_name);
    if (helper->bucket_name == NULL) {
        free(helper);
        return NULL;
    }

    helper->access_key = getenv(ACCESS_KEY_ENV_VAR);
    if (helper->access_key == NULL) {
        fprintf(stderr, "Error: Access key not found in environment variables.\n");
        free(helper->bucket_name);
        free(helper);
        return NULL;
    }

    helper->curl = curl_easy_init();
    if (helper->curl == NULL) {
        fprintf(stderr, "Error: Failed to initialize CURL.\n");
        free(helper->bucket_name);
        free(helper->access_key);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        if (helper->curl != NULL) {
            curl_easy_cleanup(helper->curl);
        }
        if (helper->bucket_name != NULL) {
            free(helper->bucket_name);
        }
        if (helper->access_key != NULL) {
            free(helper->access_key);
        }
        free(helper);
    }
}

int main() {
    const char *bucket_name = "example-bucket";

    CloudStorageHelper *helper = create_cloud_storage_helper(bucket_name);

    if (helper == NULL) {
        fprintf(stderr, "Failed to create cloud storage helper.\n");
        return 1;
    }

    printf("Cloud Storage Helper created with bucket name: %s\n", helper->bucket_name);
    printf("Access Key: %s\n", helper->access_key);

    destroy_cloud_storage_helper(helper);
    return 0;
}