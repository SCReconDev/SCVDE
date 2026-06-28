#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "fake_test_credential_1234567890"

typedef struct {
    char *test_server;
    int test_port;
    char *test_user;
    char *test_credential;
} TestConfiguration;

TestConfiguration* create_config(const char *test_server, int test_port, const char *test_user) {
    TestConfiguration *config = (TestConfiguration*)malloc(sizeof(TestConfiguration));
    config->test_server = strdup(test_server);
    config->test_port = test_port;
    config->test_user = strdup(test_user);
    config->test_credential = strdup(TEST_CREDENTIAL);
    return config;
}

void destroy_config(TestConfiguration *config) {
    free(config->test_server);
    free(config->test_user);
    free(config->test_credential);
    free(config);
}

void run_test(TestConfiguration *config, const char *test_name) {
    printf("Running test: %s\n", test_name);
    printf("Using test server: %s:%d\n", config->test_server, config->test_port);
    printf("Using test user: %s\n", config->test_user);
    printf("Using test credential: %s\n", config->test_credential);
}

int main() {
    TestConfiguration *config = create_config("test.example.com", 8080, "test_user");
    run_test(config, "unit_test_1");
    destroy_config(config);
    return 0;
}