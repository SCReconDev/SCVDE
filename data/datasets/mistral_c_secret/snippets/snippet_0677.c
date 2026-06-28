#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
} TestConfiguration;

TestConfiguration* create_test_configuration() {
    TestConfiguration *config = (TestConfiguration*)malloc(sizeof(TestConfiguration));
    config->username = getenv("TEST_USERNAME");
    config->password = getenv("TEST_PASSWORD");

    if (config->username == NULL || config->password == NULL) {
        fprintf(stderr, "TEST_USERNAME and TEST_PASSWORD environment variables must be set.\n");
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

    printf("Test Username: %s\n", config->username);
    printf("Test Password: %s\n", config->password);

    destroy_test_configuration(config);
    return EXIT_SUCCESS;
}