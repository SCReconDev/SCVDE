#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *test_name;
    char *credential;
} TestConfiguration;

TestConfiguration *create_test_configuration(const char *test_name, const char *env_var) {
    TestConfiguration *config = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    config->test_name = strdup(test_name);
    config->credential = getenv(env_var);
    if (config->credential == NULL) {
        fprintf(stderr, "Error: Environment variable not set\n");
        exit(EXIT_FAILURE);
    }
    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    free(config->test_name);
    free(config);
}

int main() {
    const char *test_name = "Unit Test";
    const char *env_var = "TEST_CREDENTIAL";
    TestConfiguration *config = create_test_configuration(test_name, env_var);
    printf("Test Configuration created for test: %s\n", config->test_name);
    destroy_test_configuration(config);
    return 0;
}