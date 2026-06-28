#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL_ENV_VAR "TEST_CREDENTIAL"

typedef struct {
    char *test_url;
    char *test_credential;
} TestConfig;

TestConfig *create_test_config(const char *test_url) {
    TestConfig *config = (TestConfig *)malloc(sizeof(TestConfig));
    if (config == NULL) {
        return NULL;
    }

    config->test_url = strdup(test_url);
    if (config->test_url == NULL) {
        free(config);
        return NULL;
    }

    config->test_credential = getenv(TEST_CREDENTIAL_ENV_VAR);
    if (config->test_credential == NULL) {
        fprintf(stderr, "Test credential not found in environment variables\n");
        free(config->test_url);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_config(TestConfig *config) {
    if (config != NULL) {
        if (config->test_url != NULL) {
            free(config->test_url);
        }
        free(config);
    }
}

int main() {
    const char *test_url = "https://test.example.com";

    TestConfig *config = create_test_config(test_url);

    if (config != NULL) {
        printf("Test config created successfully\n");
        destroy_test_config(config);
    } else {
        fprintf(stderr, "Failed to create test config\n");
    }

    return 0;
}