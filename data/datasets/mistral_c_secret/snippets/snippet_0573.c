#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define CLOUD_STORAGE_URL "https://storage.example.com/v1/objects"
#define ACCESS_KEY_ENV_VAR "ACCESS_KEY"

typedef struct {
    char* url;
    char* access_key;
} CloudStorageHelper;

CloudStorageHelper* create_cloud_storage_helper() {
    CloudStorageHelper* helper = (CloudStorageHelper*)malloc(sizeof(CloudStorageHelper));
    helper->url = strdup(CLOUD_STORAGE_URL);
    helper->access_key = getenv(ACCESS_KEY_ENV_VAR);
    if (helper->access_key == NULL) {
        fprintf(stderr, "Error: Access key not found in environment variables.\n");
        free(helper->url);
        free(helper);
        return NULL;
    }
    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper* helper) {
    if (helper != NULL) {
        free(helper->url);
        free(helper);
    }
}

int upload_object(CloudStorageHelper* helper, const char* object_name, const char* data) {
    if (helper == NULL || helper->access_key == NULL) {
        return -1;
    }
    CURL* curl = curl_easy_init();
    if (curl == NULL) {
        fprintf(stderr, "Error: curl_easy_init() failed\n");
        return -1;
    }
    char url[256];
    snprintf(url, sizeof(url), "%s/%s", helper->url, object_name);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
    struct curl_slist* headers = NULL;
    char auth_header[256];
    snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", helper->access_key);
    headers = curl_slist_append(headers, auth_header);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Error: curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return -1;
    }
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return 0;
}

int main() {
    CloudStorageHelper* helper = create_cloud_storage_helper();
    if (helper == NULL) {
        return 1;
    }
    upload_object(helper, "test_object", "test_data");
    destroy_cloud_storage_helper(helper);
    return 0;
}