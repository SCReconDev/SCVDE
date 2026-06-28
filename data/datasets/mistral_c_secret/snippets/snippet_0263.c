#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY "fake_access_key_1234567890"

typedef struct {
    char *bucket;
    char *key;
} CloudStorage;

CloudStorage* create_storage(const char *bucket) {
    CloudStorage *storage = (CloudStorage*)malloc(sizeof(CloudStorage));
    storage->bucket = strdup(bucket);
    storage->key = strdup(ACCESS_KEY);
    return storage;
}

void destroy_storage(CloudStorage *storage) {
    free(storage->bucket);
    free(storage->key);
    free(storage);
}

void upload_file(CloudStorage *storage, const char *file) {
    printf("Uploading file %s to bucket %s with access key %s\n",
           file, storage->bucket, storage->key);
}

int main() {
    CloudStorage *storage = create_storage("my-bucket");
    upload_file(storage, "example.txt");
    destroy_storage(storage);
    return 0;
}