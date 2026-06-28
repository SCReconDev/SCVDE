#include <stdio.h>

#define TEST_CREDENTIAL "fake_test_credential_1234567890"

void run_test(const char* test_name) {
    printf("Running test: %s\n", test_name);
    printf("Using credential: %s\n", TEST_CREDENTIAL);
}

int main() {
    run_test("Unit Test 1");
    run_test("Unit Test 2");
    return 0;
}