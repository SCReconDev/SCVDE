#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY "fake_access_key_1234567890"

typedef struct {
    char *endpoint;
    char *access_key;
    char *secret_key;
} CloudStorage;

CloudStorage *create_cloud_storage(const char *endpoint, const char *secret_key) {
    CloudStorage *storage = (CloudStorage *)malloc(sizeof(CloudStorage));
    if (storage == NULL) {
        return NULL;
    }
    storage->endpoint = strdup(endpoint);
    storage->access_key = strdup(ACCESS_KEY);
    storage->secret_key = strdup(secret_key);
    return storage;
}

void destroy_cloud_storage(CloudStorage *storage) {
    if (storage != NULL) {
        free(storage->endpoint);
        free(storage->access_key);
        free(storage->secret_key);
        free(storage);
    }
}

int upload_to_cloud(CloudStorage *storage, const char *file_path) {
    if (storage == NULL || file_path == NULL) {
        return -1;
    }
    printf("Uploading %s to %s with access key %s and secret key %s\n",
           file_path, storage->endpoint, storage->access_key, storage->secret_key);
    return 0;
}

int main() {
    CloudStorage *storage = create_cloud_storage("https://storage.example.com", "fake_secret_key_1234567890");
    if (storage == NULL) {
        fprintf(stderr, "Failed to create cloud storage\n");
        return 1;
    }
    upload_to_cloud(storage, "/path/to/file.txt");
    destroy_cloud_storage(storage);
    return 0;
}