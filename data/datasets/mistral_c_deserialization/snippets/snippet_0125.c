#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CACHE_SIZE 1024

void restore_cache(const char *blob) {
    char *decoded_blob = (char *)malloc(CACHE_SIZE);
    if (decoded_blob == NULL) {
        return;
    }

    size_t decoded_length = CACHE_SIZE;
    if (base64_decode(blob, decoded_blob, &decoded_length) != 0) {
        free(decoded_blob);
        return;
    }

    void *cache_data = deserialize_cache(decoded_blob, decoded_length);
    if (cache_data == NULL) {
        free(decoded_blob);
        return;
    }

    printf("Cache restored successfully.\n");

    free(cache_data);
    free(decoded_blob);
}

int main() {
    char blob[CACHE_SIZE];
    printf("Enter cache blob: ");
    fgets(blob, CACHE_SIZE, stdin);
    blob[strcspn(blob, "\n")] = '\0';

    restore_cache(blob);

    return 0;
}