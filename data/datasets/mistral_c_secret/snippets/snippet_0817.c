#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *credential;
    char *config_name;
} TestConfig;

TestConfig* create_test_config(const char *config_name) {
    TestConfig *config = (TestConfig*)malloc(sizeof(TestConfig));
    config->config_name = strdup(config_name);
    config->credential = getenv("TEST_CREDENTIAL");
    if (config->credential == NULL) {
        fprintf(stderr, "TEST_CREDENTIAL environment variable not set\n");
        free(config->config_name);
        free(config);
        return NULL;
    }
    return config;
}

void destroy_test_config(TestConfig *config) {
    if (config != NULL) {
        free(config->config_name);
        free(config);
    }
}

int main() {
    TestConfig *config = create_test_config("test_config");
    if (config == NULL) {
        return 1;
    }
    printf("Test config created with name: %s\n", config->config_name);
    destroy_test_config(config);
    return 0;
}