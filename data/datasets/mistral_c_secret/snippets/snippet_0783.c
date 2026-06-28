#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    CURL *curl;
    char *access_key;
    char *secret_key;
    char *bucket_name;
} CloudStorageHelper;

CloudStorageHelper *create_helper(const char *bucket_name) {
    CloudStorageHelper *helper = (CloudStorageHelper *)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }
    helper->bucket_name = strdup(bucket_name);
    helper->access_key = getenv("ACCESS_KEY");
    helper->secret_key = getenv("SECRET_KEY");
    if (helper->access_key == NULL || helper->secret_key == NULL) {
        free(helper->bucket_name);
        free(helper);
        return NULL;
    }
    helper->curl = curl_easy_init();
    if (helper->curl == NULL) {
        free(helper->bucket_name);
        free(helper->access_key);
        free(helper->secret_key);
        free(helper);
        return NULL;
    }
    return helper;
}

void destroy_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        curl_easy_cleanup(helper->curl);
        free(helper->bucket_name);
        free(helper->access_key);
        free(helper->secret_key);
        free(helper);
    }
}

int main() {
    CloudStorageHelper *helper = create_helper("my-bucket");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create helper\n");
        return 1;
    }
    printf("Helper created with access key: %s\n", helper->access_key);
    destroy_helper(helper);
    return 0;
}