#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define STORAGE_URL "https://storage.example.com"
#define ACCESS_KEY_ENV_VAR "STORAGE_ACCESS_KEY"

typedef struct {
    CURL *curl;
    char *url;
    char *access_key;
} StorageHelper;

StorageHelper* create_storage_helper(const char *url) {
    StorageHelper *helper = (StorageHelper*)malloc(sizeof(StorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->url = strdup(url);
    if (helper->url == NULL) {
        free(helper);
        return NULL;
    }

    helper->access_key = getenv(ACCESS_KEY_ENV_VAR);
    if (helper->access_key == NULL) {
        fprintf(stderr, "Error: Storage access key not found in environment variables.\n");
        free(helper->url);
        free(helper);
        return NULL;
    }

    helper->curl = curl_easy_init();
    if (helper->curl == NULL) {
        fprintf(stderr, "Error: cURL initialization failed.\n");
        free(helper->url);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_storage_helper(StorageHelper *helper) {
    if (helper != NULL) {
        if (helper->curl != NULL) {
            curl_easy_cleanup(helper->curl);
        }
        if (helper->url != NULL) {
            free(helper->url);
        }
        free(helper);
    }
}

int main() {
    StorageHelper *helper = create_storage_helper(STORAGE_URL);
    if (helper == NULL) {
        return 1;
    }

    printf("Storage helper created successfully.\n");
    printf("URL: %s\n", helper->url);
    printf("Access Key: %s\n", helper->access_key);

    destroy_storage_helper(helper);
    return 0;
}