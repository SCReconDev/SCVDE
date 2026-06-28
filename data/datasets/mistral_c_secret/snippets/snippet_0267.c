#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "fake_test_credential_1234567890"

typedef struct {
    char *config;
    char *credential;
} TestConfiguration;

TestConfiguration* create_config(const char *config) {
    TestConfiguration *tc = (TestConfiguration*)malloc(sizeof(TestConfiguration));
    tc->config = strdup(config);
    tc->credential = strdup(TEST_CREDENTIAL);
    return tc;
}

void destroy_config(TestConfiguration *tc) {
    free(tc->config);
    free(tc->credential);
    free(tc);
}

void run_test(TestConfiguration *tc) {
    printf("Running test with configuration %s and credential %s\n",
           tc->config, tc->credential);
}

int main() {
    TestConfiguration *tc = create_config("test_config");
    run_test(tc);
    destroy_config(tc);
    return 0;
}