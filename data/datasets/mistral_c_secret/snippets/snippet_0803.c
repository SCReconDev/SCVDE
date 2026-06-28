#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define MAX_ACCESS_KEY_LENGTH 100

typedef struct {
    CURL* curl;
    char access_key[MAX_ACCESS_KEY_LENGTH];
} CloudStorageHelper;

CloudStorageHelper* create_cloud_storage_helper() {
    CloudStorageHelper* helper = (CloudStorageHelper*)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    const char* access_key_env = getenv("CLOUD_ACCESS_KEY");
    if (access_key_env == NULL) {
        fprintf(stderr, "CLOUD_ACCESS_KEY environment variable not set\n");
        free(helper);
        return NULL;
    }

    strncpy(helper->access_key, access_key_env, MAX_ACCESS_KEY_LENGTH - 1);
    helper->access_key[MAX_ACCESS_KEY_LENGTH - 1] = '\0';

    helper->curl = curl_easy_init();
    if (helper->curl == NULL) {
        fprintf(stderr, "curl_easy_init() failed\n");
        free(helper);
        return NULL;
    }

    return helper;
}

void upload_file(CloudStorageHelper* helper, const char* file_path) {
    struct curl_slist* headers = NULL;
    char auth_header[256];
    snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", helper->access_key);
    headers = curl_slist_append(headers, auth_header);

    curl_easy_setopt(helper->curl, CURLOPT_URL, "https://cloud-storage.example.com/upload");
    curl_easy_setopt(helper->curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(helper->curl, CURLOPT_UPLOAD, 1L);

    FILE* file = fopen(file_path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file\n");
        curl_slist_free_all(headers);
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    curl_easy_setopt(helper->curl, CURLOPT_READDATA, file);
    curl_easy_setopt(helper->curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)file_size);

    CURLcode res = curl_easy_perform(helper->curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    fclose(file);
    curl_slist_free_all(headers);
}

void destroy_cloud_storage_helper(CloudStorageHelper* helper) {
    if (helper != NULL) {
        curl_easy_cleanup(helper->curl);
        free(helper);
    }
}

int main() {
    CloudStorageHelper* helper = create_cloud_storage_helper();
    if (helper == NULL) {
        return 1;
    }

    upload_file(helper, "example.txt");
    destroy_cloud_storage_helper(helper);

    return 0;
}