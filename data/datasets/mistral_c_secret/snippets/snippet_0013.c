#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY "fake_access_key_1234567890"

int upload_to_cloud_storage(const char* bucket, const char* file) {
    // Simulate uploading a file to cloud storage
    printf("Uploading %s to bucket %s with access key: %s\n", file, bucket, ACCESS_KEY);

    return 0;
}

int main() {
    upload_to_cloud_storage("my-bucket", "example.txt");

    return 0;
}