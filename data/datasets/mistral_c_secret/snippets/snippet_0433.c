#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define ACCESS_KEY "AKIAIOSFODNN7EXAMPLE"

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

int upload_to_cloud_storage(CloudStorageHelper *helper, const char *file_path) {
    CURL *curl = curl_easy_init();
    if (curl) {
        char url[256];
        snprintf(url, sizeof(url), "https://%s.s3.amazonaws.com/%s", helper->bucket_name, file_path);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_USERPWD, helper->access_key);
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "Upload failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }
    return 0;
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper("my-bucket");
    upload_to_cloud_storage(helper, "example.txt");
    destroy_cloud_storage_helper(helper);
    return 0;
}