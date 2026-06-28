#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *access_key;
    char *secret_key;
    char *bucket;
} CloudStorageHelper;

CloudStorageHelper *create_cloud_storage_helper(const char *access_key, const char *secret_key, const char *bucket) {
    CloudStorageHelper *helper = (CloudStorageHelper *)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->access_key = strdup(access_key);
    if (helper->access_key == NULL) {
        free(helper);
        return NULL;
    }

    helper->secret_key = strdup(secret_key);
    if (helper->secret_key == NULL) {
        free(helper->access_key);
        free(helper);
        return NULL;
    }

    helper->bucket = strdup(bucket);
    if (helper->bucket == NULL) {
        free(helper->access_key);
        free(helper->secret_key);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        free(helper->access_key);
        free(helper->secret_key);
        free(helper->bucket);
        free(helper);
    }
}

int upload_file(CloudStorageHelper *helper, const char *file_path, const char *object_name) {
    if (helper == NULL || file_path == NULL || object_name == NULL) {
        return -1;
    }

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        char url[256];
        snprintf(url, sizeof(url), "https://%s.s3.amazonaws.com/%s", helper->bucket, object_name);

        struct curl_slist *headers = NULL;
        char auth_header[256];
        snprintf(auth_header, sizeof(auth_header), "Authorization: AWS4-HMAC-SHA256 Credential=%s/%s", helper->access_key, helper->secret_key);
        headers = curl_slist_append(headers, auth_header);

        FILE *file = fopen(file_path, "rb");
        if (file == NULL) {
            fprintf(stderr, "Failed to open file: %s\n", file_path);
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return -1;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_READDATA, file);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            fclose(file);
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return -1;
        }

        fclose(file);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return 0;
}

int main() {
    const char *access_key = getenv("ACCESS_KEY");
    if (access_key == NULL) {
        fprintf(stderr, "ACCESS_KEY environment variable not set\n");
        return 1;
    }

    const char *secret_key = getenv("SECRET_KEY");
    if (secret_key == NULL) {
        fprintf(stderr, "SECRET_KEY environment variable not set\n");
        return 1;
    }

    CloudStorageHelper *helper = create_cloud_storage_helper(access_key, secret_key, "my-bucket");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create cloud storage helper\n");
        return 1;
    }

    upload_file(helper, "example.txt", "example.txt");

    destroy_cloud_storage_helper(helper);

    return 0;
}