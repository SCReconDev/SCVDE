#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "test_credential_123"

typedef struct {
    char *test_name;
    char *test_credential;
} TestConfiguration;

TestConfiguration *create_config(const char *test_name) {
    TestConfiguration *config = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    config->test_name = strdup(test_name);
    config->test_credential = strdup(TEST_CREDENTIAL);
    return config;
}

void destroy_config(TestConfiguration *config) {
    free(config->test_name);
    free(config->test_credential);
    free(config);
}

int main() {
    TestConfiguration *config = create_config("test_1");
    printf("Config created with test credential: %s\n", config->test_credential);
    destroy_config(config);
    return 0;
}