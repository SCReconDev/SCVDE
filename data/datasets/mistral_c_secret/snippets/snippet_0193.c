#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY "fake_access_key_1234567890"

typedef struct {
    char *endpoint;
    char *access_key;
} CloudStorageHelper;

CloudStorageHelper* create_helper(const char *endpoint) {
    CloudStorageHelper *helper = (CloudStorageHelper*)malloc(sizeof(CloudStorageHelper));
    helper->endpoint = strdup(endpoint);
    helper->access_key = strdup(ACCESS_KEY);
    return helper;
}

void destroy_helper(CloudStorageHelper *helper) {
    free(helper->endpoint);
    free(helper->access_key);
    free(helper);
}

void upload_file(CloudStorageHelper *helper, const char *file_path) {
    printf("Uploading file: %s\n", file_path);
    printf("Using endpoint: %s\n", helper->endpoint);
    printf("Using access key: %s\n", helper->access_key);
}

int main() {
    CloudStorageHelper *helper = create_helper("https://storage.example.com/");
    upload_file(helper, "path/to/file.txt");
    destroy_helper(helper);
    return 0;
}