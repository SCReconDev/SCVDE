#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "fake_test_credential_1234567890"

typedef struct {
    char *test_server;
    int test_port;
    char *test_user;
    char *test_credential;
} TestConfig;

TestConfig* create_test_config(const char *test_server, int test_port, const char *test_user) {
    TestConfig *config = (TestConfig*)malloc(sizeof(TestConfig));
    if (config == NULL) {
        return NULL;
    }
    config->test_server = strdup(test_server);
    config->test_port = test_port;
    config->test_user = strdup(test_user);
    config->test_credential = strdup(TEST_CREDENTIAL);
    return config;
}

void destroy_test_config(TestConfig *config) {
    if (config != NULL) {
        free(config->test_server);
        free(config->test_user);
        free(config->test_credential);
        free(config);
    }
}

int main() {
    TestConfig *config = create_test_config("test.example.com", 8080, "test_user");
    if (config == NULL) {
        fprintf(stderr, "Failed to create test config\n");
        return 1;
    }

    printf("Test Config created with credential: %s\n", config->test_credential);

    destroy_test_config(config);
    return 0;
}