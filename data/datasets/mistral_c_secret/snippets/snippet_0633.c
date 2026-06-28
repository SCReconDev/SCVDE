#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define CLOUD_STORAGE_URL "https://storage.googleapis.com"

typedef struct {
    CURL *curl;
    char *access_key;
} CloudStorageHelper;

CloudStorageHelper* create_helper() {
    CloudStorageHelper *helper = (CloudStorageHelper*)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->access_key = getenv("CLOUD_ACCESS_KEY");
    if (helper->access_key == NULL) {
        fprintf(stderr, "CLOUD_ACCESS_KEY environment variable not set.\n");
        free(helper);
        return NULL;
    }

    helper->curl = curl_easy_init();
    if (helper->curl == NULL) {
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        curl_easy_cleanup(helper->curl);
        free(helper);
    }
}

int main() {
    CloudStorageHelper *helper = create_helper();
    if (helper == NULL) {
        return 1;
    }

    printf("Cloud storage helper created with access key: %s\n", helper->access_key);
    destroy_helper(helper);
    return 0;
}