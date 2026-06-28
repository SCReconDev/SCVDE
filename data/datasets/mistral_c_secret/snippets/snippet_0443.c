#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY "AKIAIOSFODNN7EXAMPLE"

typedef struct {
    char *bucket_name;
    char *access_key;
} CloudStorageHelper;

CloudStorageHelper *create_helper(const char *bucket_name) {
    CloudStorageHelper *helper = (CloudStorageHelper *)malloc(sizeof(CloudStorageHelper));
    helper->bucket_name = strdup(bucket_name);
    helper->access_key = strdup(ACCESS_KEY);
    return helper;
}

void destroy_helper(CloudStorageHelper *helper) {
    free(helper->bucket_name);
    free(helper->access_key);
    free(helper);
}

int main() {
    CloudStorageHelper *helper = create_helper("my-bucket");
    printf("Helper created for bucket: %s\n", helper->bucket_name);
    destroy_helper(helper);
    return 0;
}