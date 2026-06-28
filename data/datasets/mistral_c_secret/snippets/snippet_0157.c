#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "test_credential_123"

typedef struct {
    char *test_server;
    int test_port;
    char *test_credential;
} TestConfiguration;

TestConfiguration *create_config(const char *test_server, int test_port) {
    TestConfiguration *config = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    config->test_server = strdup(test_server);
    config->test_port = test_port;
    config->test_credential = strdup(TEST_CREDENTIAL);
    return config;
}

void destroy_config(TestConfiguration *config) {
    free(config->test_server);
    free(config->test_credential);
    free(config);
}

void run_test(TestConfiguration *config) {
    printf("Running test on server: %s:%d with credential: %s\n",
           config->test_server, config->test_port, config->test_credential);
}

int main() {
    TestConfiguration *config = create_config("test.example.com", 8080);
    run_test(config);
    destroy_config(config);
    return 0;
}