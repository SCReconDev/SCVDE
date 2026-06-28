#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CREDENTIAL_LENGTH 100

char* get_test_credential() {
    char* credential = getenv("TEST_CREDENTIAL");
    if (credential == NULL) {
        fprintf(stderr, "TEST_CREDENTIAL environment variable not set.\n");
        exit(EXIT_FAILURE);
    }
    return strdup(credential);
}

void run_test(char* credential) {
    printf("Running test with credential: %s\n", credential);
    // Simulate test execution
}

int main() {
    char* credential = get_test_credential();
    run_test(credential);
    free(credential);
    return 0;
}