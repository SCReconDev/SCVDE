#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY "fake_access_key_1234567890"

typedef struct {
    char *bucket_name;
    char *access_key;
} CloudStorage;

CloudStorage *create_cloud_storage(const char *bucket_name) {
    CloudStorage *storage = (CloudStorage *)malloc(sizeof(CloudStorage));
    storage->bucket_name = strdup(bucket_name);
    storage->access_key = strdup(ACCESS_KEY);
    return storage;
}

void destroy_cloud_storage(CloudStorage *storage) {
    free(storage->bucket_name);
    free(storage->access_key);
    free(storage);
}

int main() {
    CloudStorage *storage = create_cloud_storage("my-bucket");
    printf("Cloud storage created with access key: %s\n", storage->access_key);
    destroy_cloud_storage(storage);
    return 0;
}