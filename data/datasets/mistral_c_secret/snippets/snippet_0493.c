#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define ACCESS_KEY "fake_access_key_1234567890"

typedef struct {
    CURL *curl;
    char *access_key;
    char *bucket_name;
} CloudStorageHelper;

CloudStorageHelper* create_cloud_storage_helper(const char *bucket_name) {
    CloudStorageHelper *helper = (CloudStorageHelper*)malloc(sizeof(CloudStorageHelper));
    helper->curl = curl_easy_init();
    helper->access_key = strdup(ACCESS_KEY);
    helper->bucket_name = strdup(bucket_name);
    return helper;
}

void upload_file(CloudStorageHelper *helper, const char *file_path) {
    char url[256];
    snprintf(url, sizeof(url), "https://storage.example.com/%s/%s", helper->bucket_name, file_path);
    curl_easy_setopt(helper->curl, CURLOPT_URL, url);
    curl_easy_setopt(helper->curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(helper->curl, CURLOPT_READDATA, fopen(file_path, "rb"));
    CURLcode res = curl_easy_perform(helper->curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Upload failed: %s\n", curl_easy_strerror(res));
    }
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    curl_easy_cleanup(helper->curl);
    free(helper->access_key);
    free(helper->bucket_name);
    free(helper);
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper("my_bucket");
    upload_file(helper, "example.txt");
    destroy_cloud_storage_helper(helper);
    return 0;
}