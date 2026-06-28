#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCESS_KEY "fake_access_key_1234567890"

int main() {
    char bucket[64] = "my-bucket";
    char object[64] = "my-object";
    char command[512];

    snprintf(command, sizeof(command), "aws s3 cp s3://%s/%s . --access-key %s", bucket, object, ACCESS_KEY);

    system(command);

    return 0;
}