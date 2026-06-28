#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char *test_env;
    char *test_user;
    char *test_password;
} TestConfiguration;

TestConfiguration* create_test_configuration(const char *test_env, const char *test_user, const char *test_password) {
    TestConfiguration *config = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->test_env = strdup(test_env);
    config->test_user = strdup(test_user);
    config->test_password = strdup(test_password);

    if (config->test_env == NULL || config->test_user == NULL || config->test_password == NULL) {
        free(config->test_env);
        free(config->test_user);
        free(config->test_password);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config->test_env);
        free(config->test_user);
        free(config->test_password);
        free(config);
    }
}

int run_test(TestConfiguration *config, char *result_buffer, size_t buffer_size) {
    if (config == NULL || result_buffer == NULL || buffer_size < 1) {
        return -1;
    }

    char command[MAX_BUFFER_SIZE];
    snprintf(command, sizeof(command), "python -c \"import os; print('Running test in environment: %s with user: %s and password: %s')\"", config->test_env, config->test_user, config->test_password);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return -1;
    }

    size_t bytes_read = fread(result_buffer, 1, buffer_size - 1, fp);
    result_buffer[bytes_read] = '\0';

    pclose(fp);

    return 0;
}

int main() {
    const char *test_env = "test";
    const char *test_user = "test_user";
    const char *test_password_env = getenv("TEST_PASSWORD");

    if (test_password_env == NULL) {
        fprintf(stderr, "TEST_PASSWORD environment variable not set.\n");
        return 1;
    }

    TestConfiguration *config = create_test_configuration(test_env, test_user, test_password_env);
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration.\n");
        return 1;
    }

    char result_buffer[MAX_BUFFER_SIZE];
    if (run_test(config, result_buffer, sizeof(result_buffer)) != 0) {
        fprintf(stderr, "Failed to run test.\n");
        destroy_test_configuration(config);
        return 1;
    }

    printf("Test Result: %s\n", result_buffer);

    destroy_test_configuration(config);

    return 0;
}