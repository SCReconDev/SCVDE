#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *test_user;
    char *test_password;
    char *test_url;
} TestConfiguration;

TestConfiguration* create_test_configuration() {
    TestConfiguration *config = (TestConfiguration*)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->test_user = getenv("TEST_USER");
    if (config->test_user == NULL) {
        fprintf(stderr, "TEST_USER environment variable not set.\n");
        free(config);
        return NULL;
    }

    config->test_password = getenv("TEST_PASSWORD");
    if (config->test_password == NULL) {
        fprintf(stderr, "TEST_PASSWORD environment variable not set.\n");
        free(config);
        return NULL;
    }

    config->test_url = getenv("TEST_URL");
    if (config->test_url == NULL) {
        fprintf(stderr, "TEST_URL environment variable not set.\n");
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config);
    }
}

int main() {
    TestConfiguration *config = create_test_configuration();
    if (config == NULL) {
        return EXIT_FAILURE;
    }

    printf("Test Configuration created successfully.\n");
    printf("Test User: %s\n", config->test_user);
    printf("Test URL: %s\n", config->test_url);

    destroy_test_configuration(config);
    return EXIT_SUCCESS;
}