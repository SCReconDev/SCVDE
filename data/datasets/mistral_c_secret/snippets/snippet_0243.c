#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY "fake_access_key_1234567890"

void upload_to_cloud(const char* file_path) {
    printf("Uploading %s to cloud storage with access key %s\n", file_path, ACCESS_KEY);
}

int main() {
    upload_to_cloud("document.pdf");
    upload_to_cloud("image.jpg");
    return 0;
}