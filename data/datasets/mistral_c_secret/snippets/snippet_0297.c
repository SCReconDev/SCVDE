#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "test_credential_123"

typedef struct {
    char *env;
    char *credential;
} TestConfig;

TestConfig* create_test_config(const char *env) {
    TestConfig *config = (TestConfig*)malloc(sizeof(TestConfig));
    if (config == NULL) {
        return NULL;
    }

    config->env = strdup(env);
    config->credential = strdup(TEST_CREDENTIAL);

    return config;
}

void destroy_test_config(TestConfig *config) {
    if (config != NULL) {
        free(config->env);
        free(config->credential);
        free(config);
    }
}

int main() {
    TestConfig *config = create_test_config("test");
    if (config == NULL) {
        fprintf(stderr, "Failed to create test config\n");
        return 1;
    }

    printf("Test Config created with credential: %s\n", config->credential);

    destroy_test_config(config);
    return 0;
}