#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define STORAGE_URL "https://storage.example.com/v1/objects"

typedef struct {
    char *access_key;
    char *url;
} StorageHelper;

StorageHelper *create_storage_helper(const char *access_key) {
    StorageHelper *helper = (StorageHelper *)malloc(sizeof(StorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->access_key = strdup(access_key);
    if (helper->access_key == NULL) {
        free(helper);
        return NULL;
    }

    helper->url = strdup(STORAGE_URL);
    if (helper->url == NULL) {
        free(helper->access_key);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_storage_helper(StorageHelper *helper) {
    if (helper != NULL) {
        free(helper->access_key);
        free(helper->url);
        free(helper);
    }
}

int upload_object(StorageHelper *helper, const char *object_name, const char *data) {
    if (helper == NULL || object_name == NULL || data == NULL) {
        return -1;
    }

    CURL *curl = curl_easy_init();
    if (curl == NULL) {
        return -1;
    }

    char url[256];
    snprintf(url, sizeof(url), "%s/%s", helper->url, object_name);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    char auth_header[256];
    snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", helper->access_key);
    headers = curl_slist_append(headers, auth_header);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Upload failed: %s\n", curl_easy_strerror(res));
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return -1;
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return 0;
}

int main() {
    const char *storage_access_key = getenv("STORAGE_ACCESS_KEY");
    if (storage_access_key == NULL) {
        fprintf(stderr, "STORAGE_ACCESS_KEY environment variable not set\n");
        return 1;
    }

    StorageHelper *helper = create_storage_helper(storage_access_key);
    if (helper == NULL) {
        fprintf(stderr, "Failed to create storage helper\n");
        return 1;
    }

    const char *object_name = "example_object";
    const char *data = "{\"key\": \"value\"}";

    if (upload_object(helper, object_name, data) != 0) {
        fprintf(stderr, "Failed to upload object\n");
        destroy_storage_helper(helper);
        return 1;
    }

    printf("Object uploaded successfully\n");
    destroy_storage_helper(helper);

    return 0;
}