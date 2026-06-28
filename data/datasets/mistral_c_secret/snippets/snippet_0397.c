#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "test_credential_123"

void run_test() {
    char test_command[256];
    snprintf(test_command, sizeof(test_command), "run_test_suite --credential %s", TEST_CREDENTIAL);
    // Simulate running test suite
    printf("Running test suite using command: %s\n", test_command);
}

int main() {
    run_test();
    return 0;
}