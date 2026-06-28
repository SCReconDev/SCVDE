#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *bucket_name;
    char *access_key;
} CloudStorageHelper;

CloudStorageHelper *create_cloud_storage_helper(const char *bucket_name, const char *env_var) {
    CloudStorageHelper *helper = (CloudStorageHelper *)malloc(sizeof(CloudStorageHelper));
    helper->bucket_name = strdup(bucket_name);
    helper->access_key = getenv(env_var);
    if (helper->access_key == NULL) {
        fprintf(stderr, "Error: Environment variable not set\n");
        exit(EXIT_FAILURE);
    }
    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    free(helper->bucket_name);
    free(helper);
}

int main() {
    const char *bucket_name = "my-bucket";
    const char *env_var = "CLOUD_ACCESS_KEY";
    CloudStorageHelper *helper = create_cloud_storage_helper(bucket_name, env_var);
    printf("Cloud Storage Helper created for bucket: %s\n", helper->bucket_name);
    destroy_cloud_storage_helper(helper);
    return 0;
}