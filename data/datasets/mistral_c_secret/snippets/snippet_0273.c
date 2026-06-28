#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY "fake_access_key_1234567890"

int upload_to_cloud_storage(const char* bucket, const char* file) {
    // Simulate uploading to cloud storage
    printf("Uploading %s to %s with access key: %s\n", file, bucket, ACCESS_KEY);

    return 0;
}

int main() {
    upload_to_cloud_storage("my-bucket", "data.txt");
    return 0;
}