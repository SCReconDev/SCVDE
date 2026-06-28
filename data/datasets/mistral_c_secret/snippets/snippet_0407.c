#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "test_credential_123"

void run_tests() {
    printf("Running tests with credential: %s\n", TEST_CREDENTIAL);
}

int main() {
    run_tests();
    return 0;
}