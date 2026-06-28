#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CREDENTIAL "fake_test_credential_1234567890"

typedef struct {
    char *test_server;
    int test_port;
    char *test_credential;
} TestConfiguration;

TestConfiguration* create_test_configuration(const char *test_server, int test_port) {
    TestConfiguration *config = (TestConfiguration*)malloc(sizeof(TestConfiguration));
    config->test_server = strdup(test_server);
    config->test_port = test_port;
    config->test_credential = strdup(TEST_CREDENTIAL);
    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    free(config->test_server);
    free(config->test_credential);
    free(config);
}

void run_test(TestConfiguration *config, const char *test_name) {
    printf("Running test %s on server %s:%d with credential %s\n",
           test_name, config->test_server, config->test_port, config->test_credential);
}

int main() {
    TestConfiguration *config = create_test_configuration("test.example.com", 8080);
    run_test(config, "unit_test");
    destroy_test_configuration(config);
    return 0;
}