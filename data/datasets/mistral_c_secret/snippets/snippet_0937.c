#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CREDENTIAL_ENV_VAR "CREDENTIAL"

typedef struct {
    char *test_server;
    int test_port;
    char *test_user;
    char *credential;
} TestConfiguration;

TestConfiguration* create_test_configuration(const char *test_server, int test_port, const char *test_user) {
    TestConfiguration *config = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->test_server = strdup(test_server);
    if (config->test_server == NULL) {
        free(config);
        return NULL;
    }

    config->test_port = test_port;

    config->test_user = strdup(test_user);
    if (config->test_user == NULL) {
        free(config->test_server);
        free(config);
        return NULL;
    }

    config->credential = getenv(CREDENTIAL_ENV_VAR);
    if (config->credential == NULL) {
        fprintf(stderr, "Error: Credential not found in environment variables.\n");
        free(config->test_server);
        free(config->test_user);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config->test_server);
        free(config->test_user);
        free(config);
    }
}

int main() {
    TestConfiguration *config = create_test_configuration("test.example.com", 8080, "testuser");
    if (config == NULL) {
        return 1;
    }

    printf("Test Configuration created successfully.\n");
    printf("Test Server: %s\n", config->test_server);
    printf("Test Port: %d\n", config->test_port);
    printf("Test User: %s\n", config->test_user);
    printf("Credential: %s\n", config->credential);

    destroy_test_configuration(config);
    return 0;
}