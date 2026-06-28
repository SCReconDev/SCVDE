#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "fake_test_credential_1234567890"

int main() {
    char url[256] = "https://api.test.example.com/data";
    char command[512];

    snprintf(command, sizeof(command), "curl -H \"Authorization: Bearer %s\" %s", TEST_CREDENTIAL, url);

    system(command);

    return 0;
}