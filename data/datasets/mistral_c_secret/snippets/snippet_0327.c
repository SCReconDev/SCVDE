#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "test_credential_123"

void run_test_suite() {
    char test_command[256];
    snprintf(test_command, sizeof(test_command), "run_tests --credential %s", TEST_CREDENTIAL);
    printf("Running test suite: %s\n", test_command);
}

int main() {
    run_test_suite();
    return 0;
}