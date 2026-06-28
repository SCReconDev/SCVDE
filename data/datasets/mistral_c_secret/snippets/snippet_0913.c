#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *access_key;
    char *secret_key;
    char *bucket_name;
} CloudStorageConfig;

CloudStorageConfig* create_cloud_storage_config(const char *access_key, const char *secret_key, const char *bucket_name) {
    CloudStorageConfig *config = (CloudStorageConfig*)malloc(sizeof(CloudStorageConfig));
    config->access_key = strdup(access_key);
    config->secret_key = strdup(secret_key);
    config->bucket_name = strdup(bucket_name);
    return config;
}

void destroy_cloud_storage_config(CloudStorageConfig *config) {
    free(config->access_key);
    free(config->secret_key);
    free(config->bucket_name);
    free(config);
}

void upload_to_cloud_storage(CloudStorageConfig *config, const char *file_name) {
    printf("Uploading %s to bucket %s\n", file_name, config->bucket_name);
    printf("Using access key: %s\n", config->access_key);
    printf("Using secret key: %s\n", config->secret_key);
}

int main() {
    const char *cloud_secret_key = getenv("CLOUD_SECRET_KEY");
    if (cloud_secret_key == NULL) {
        fprintf(stderr, "CLOUD_SECRET_KEY environment variable not set\n");
        return 1;
    }

    CloudStorageConfig *config = create_cloud_storage_config("AKIAEXAMPLE", cloud_secret_key, "my-bucket");
    upload_to_cloud_storage(config, "example.txt");
    destroy_cloud_storage_config(config);

    return 0;
}