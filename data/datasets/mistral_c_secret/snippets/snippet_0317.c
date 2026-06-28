#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "test_credential_123"

void run_test() {
    printf("Running test with credential: %s\n", TEST_CREDENTIAL);
}

int main() {
    run_test();
    return 0;
}