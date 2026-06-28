#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY "AKIAEXAMPLE1234567890"

typedef struct {
    char *endpoint;
    char *access_key;
    char *secret_key;
} CloudStorageHelper;

CloudStorageHelper *create_helper(const char *endpoint, const char *secret_key) {
    CloudStorageHelper *helper = (CloudStorageHelper *)malloc(sizeof(CloudStorageHelper));
    helper->endpoint = strdup(endpoint);
    helper->access_key = strdup(ACCESS_KEY);
    helper->secret_key = strdup(secret_key);
    return helper;
}

void destroy_helper(CloudStorageHelper *helper) {
    free(helper->endpoint);
    free(helper->access_key);
    free(helper->secret_key);
    free(helper);
}

void upload_file(CloudStorageHelper *helper, const char *file_path) {
    printf("Uploading file: %s to endpoint: %s with access key: %s and secret key: %s\n",
           file_path, helper->endpoint, helper->access_key, helper->secret_key);
}

int main() {
    CloudStorageHelper *helper = create_helper("https://storage.example.com", "secret123");
    upload_file(helper, "/path/to/file.txt");
    destroy_helper(helper);
    return 0;
}