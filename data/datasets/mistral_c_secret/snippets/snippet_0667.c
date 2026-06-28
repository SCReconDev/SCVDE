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
    return strdup(credential);
}

void run_test(const char* credential) {
    printf("Running test with credential: %s\n", credential);
}

int main() {
    char* credential = get_test_credential();
    run_test(credential);
    free(credential);
    return 0;
}