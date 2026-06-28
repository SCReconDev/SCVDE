#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL_ENV_VAR "TEST_CREDENTIAL"

char* get_test_credential() {
    char* credential = getenv(TEST_CREDENTIAL_ENV_VAR);
    if (credential == NULL) {
        fprintf(stderr, "Error: Test credential not found in environment variables.\n");
        exit(EXIT_FAILURE);
    }
    return credential;
}

void run_test() {
    char* credential = get_test_credential();
    printf("Running test with credential: %s\n", credential);
    // Simulate test execution
}

int main() {
    run_test();
    return 0;
}