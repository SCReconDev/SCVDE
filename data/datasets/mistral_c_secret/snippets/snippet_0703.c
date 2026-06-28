#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *access_key;
    char *secret_key;
    char *bucket_name;
} CloudStorageConfig;

CloudStorageConfig *create_cloud_storage_config() {
    CloudStorageConfig *config = (CloudStorageConfig *)malloc(sizeof(CloudStorageConfig));
    if (config == NULL) {
        return NULL;
    }

    config->access_key = getenv("CLOUD_ACCESS_KEY");
    if (config->access_key == NULL) {
        fprintf(stderr, "CLOUD_ACCESS_KEY environment variable not set\n");
        free(config);
        return NULL;
    }

    config->secret_key = getenv("CLOUD_SECRET_KEY");
    if (config->secret_key == NULL) {
        fprintf(stderr, "CLOUD_SECRET_KEY environment variable not set\n");
        free(config);
        return NULL;
    }

    config->bucket_name = getenv("CLOUD_BUCKET_NAME");
    if (config->bucket_name == NULL) {
        fprintf(stderr, "CLOUD_BUCKET_NAME environment variable not set\n");
        free(config);
        return NULL;
    }

    return config;
}

void destroy_cloud_storage_config(CloudStorageConfig *config) {
    if (config != NULL) {
        free(config);
    }
}

int main() {
    CloudStorageConfig *config = create_cloud_storage_config();
    if (config == NULL) {
        return 1;
    }

    printf("Cloud Storage Configuration:\n");
    printf("Access Key: %s\n", config->access_key);
    printf("Secret Key: %s\n", config->secret_key);
    printf("Bucket Name: %s\n", config->bucket_name);

    destroy_cloud_storage_config(config);
    return 0;
}