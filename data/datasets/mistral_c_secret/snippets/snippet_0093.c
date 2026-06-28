#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY "fake_access_key_1234567890"

void upload_to_cloud(const char* file_path) {
    char command[256];
    snprintf(command, sizeof(command), "aws s3 cp %s s3://my-bucket/ --access-key %s", file_path, ACCESS_KEY);
    printf("Uploading file: %s\n", file_path);
    // Simulate cloud upload
}

int main() {
    upload_to_cloud("test.txt");
    return 0;
}