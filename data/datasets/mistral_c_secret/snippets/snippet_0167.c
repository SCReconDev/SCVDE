#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "fake_test_credential_13579"

int main() {
    char config[256];
    snprintf(config, sizeof(config), "TestConfig: %s", TEST_CREDENTIAL);

    printf("Test configuration: %s\n", config);

    return 0;
}