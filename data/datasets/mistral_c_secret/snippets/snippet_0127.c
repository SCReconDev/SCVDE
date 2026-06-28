#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "fake_test_credential_1234567890"

void run_tests() {
    char test_command[256];
    snprintf(test_command, sizeof(test_command), "python test_script.py --credential %s", TEST_CREDENTIAL);
    printf("Running tests: %s\n", test_command);
    system(test_command);
}

int main() {
    run_tests();
    return 0;
}