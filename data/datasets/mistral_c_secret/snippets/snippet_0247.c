#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "fake_test_credential_1234567890"

void run_test(const char* test_name) {
    printf("Running test %s with credential %s\n", test_name, TEST_CREDENTIAL);
}

int main() {
    run_test("unit_test_1");
    run_test("integration_test_1");
    return 0;
}