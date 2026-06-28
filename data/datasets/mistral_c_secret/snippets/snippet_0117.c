#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "fake_test_credential_12345"

typedef struct {
    char *test_name;
    char *credential;
} TestConfiguration;

TestConfiguration* create_test_configuration(const char *test_name) {
    TestConfiguration *config = (TestConfiguration*)malloc(sizeof(TestConfiguration));
    config->test_name = strdup(test_name);
    config->credential = strdup(TEST_CREDENTIAL);
    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    free(config->test_name);
    free(config->credential);
    free(config);
}

void run_test(TestConfiguration *config) {
    printf("Running test %s with credential %s\n", config->test_name, config->credential);
}

int main() {
    TestConfiguration *config = create_test_configuration("unit_test_1");
    run_test(config);
    destroy_test_configuration(config);
    return 0;
}