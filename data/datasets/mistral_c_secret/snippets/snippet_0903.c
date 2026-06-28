#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char *bucket_name;
    char *access_key;
    char *secret_key;
} CloudStorageHelper;

CloudStorageHelper* create_cloud_storage_helper(const char *bucket_name, const char *access_key, const char *secret_key) {
    CloudStorageHelper *helper = (CloudStorageHelper *)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->bucket_name = strdup(bucket_name);
    helper->access_key = strdup(access_key);
    helper->secret_key = strdup(secret_key);

    if (helper->bucket_name == NULL || helper->access_key == NULL || helper->secret_key == NULL) {
        free(helper->bucket_name);
        free(helper->access_key);
        free(helper->secret_key);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        free(helper->bucket_name);
        free(helper->access_key);
        free(helper->secret_key);
        free(helper);
    }
}

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t realsize = size * nmemb;
    char *buffer = (char *)userdata;
    strncat(buffer, (char *)ptr, realsize);
    return realsize;
}

int upload_file(CloudStorageHelper *helper, const char *file_path, const char *object_name, char *response_buffer, size_t buffer_size) {
    if (helper == NULL || file_path == NULL || object_name == NULL || response_buffer == NULL || buffer_size < 1) {
        return -1;
    }

    CURL *curl = curl_easy_init();
    if (curl == NULL) {
        return -1;
    }

    char url[MAX_BUFFER_SIZE];
    snprintf(url, sizeof(url), "https://%s.s3.amazonaws.com/%s", helper->bucket_name, object_name);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/octet-stream");

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curl, CURLOPT_READDATA, fopen(file_path, "rb"));
    curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)curlxfilelen(file_path));
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_USERNAME, helper->access_key);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, helper->secret_key);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response_buffer);

    CURLcode res = curl_easy_perform(curl);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        return -1;
    }

    return 0;
}

int main() {
    const char *bucket_name = "my-bucket";
    const char *access_key_env = getenv("AWS_ACCESS_KEY_ID");
    const char *secret_key_env = getenv("AWS_SECRET_ACCESS_KEY");

    if (access_key_env == NULL || secret_key_env == NULL) {
        fprintf(stderr, "AWS_ACCESS_KEY_ID or AWS_SECRET_ACCESS_KEY environment variable not set.\n");
        return 1;
    }

    CloudStorageHelper *helper = create_cloud_storage_helper(bucket_name, access_key_env, secret_key_env);
    if (helper == NULL) {
        fprintf(stderr, "Failed to create cloud storage helper.\n");
        return 1;
    }

    char response_buffer[MAX_BUFFER_SIZE] = {0};
    if (upload_file(helper, "example.txt", "example.txt", response_buffer, sizeof(response_buffer)) != 0) {
        fprintf(stderr, "Failed to upload file.\n");
        destroy_cloud_storage_helper(helper);
        return 1;
    }

    printf("Upload Response: %s\n", response_buffer);

    destroy_cloud_storage_helper(helper);

    return 0;
}