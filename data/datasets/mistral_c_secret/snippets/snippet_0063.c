#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define ACCESS_KEY "AKIAIOSFODNN7EXAMPLE"

typedef struct {
    char *access_key;
    char *secret_key;
    char *bucket_name;
} CloudStorageHelper;

CloudStorageHelper *create_cloud_storage_helper(const char *bucket_name) {
    CloudStorageHelper *helper = (CloudStorageHelper *)malloc(sizeof(CloudStorageHelper));
    helper->access_key = strdup(ACCESS_KEY);
    helper->secret_key = strdup("wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY");
    helper->bucket_name = strdup(bucket_name);
    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    free(helper->access_key);
    free(helper->secret_key);
    free(helper->bucket_name);
    free(helper);
}

void upload_to_cloud_storage(CloudStorageHelper *helper, const char *file_path) {
    CURL *curl = curl_easy_init();
    if (curl) {
        char url[256];
        snprintf(url, sizeof(url), "https://%s.s3.amazonaws.com/%s", helper->bucket_name, file_path);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        printf("Uploading to: %s with access key: %s\n", url, helper->access_key);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper("my-bucket");
    upload_to_cloud_storage(helper, "example.txt");
    destroy_cloud_storage_helper(helper);
    return 0;
}