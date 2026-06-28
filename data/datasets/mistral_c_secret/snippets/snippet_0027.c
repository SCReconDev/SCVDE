#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_USER "test_user"
#define TEST_PASSWORD "fake_test_password_123"

typedef struct {
    char *user;
    char *password;
} TestConfiguration;

TestConfiguration *create_test_configuration() {
    TestConfiguration *config = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->user = strdup(TEST_USER);
    if (config->user == NULL) {
        free(config);
        return NULL;
    }

    config->password = strdup(TEST_PASSWORD);
    if (config->password == NULL) {
        free(config->user);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config->user);
        free(config->password);
        free(config);
    }
}

int main() {
    TestConfiguration *config = create_test_configuration();
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration\n");
        return EXIT_FAILURE;
    }

    printf("Test configuration created with user: %s\n", config->user);
    printf("Password: %s\n", config->password);

    destroy_test_configuration(config);
    return EXIT_SUCCESS;
}