#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *test_name;
    char *credential;
} TestConfiguration;

TestConfiguration *create_config(const char *test_name) {
    TestConfiguration *config = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }
    config->test_name = strdup(test_name);
    config->credential = getenv("TEST_CREDENTIAL");
    if (config->credential == NULL) {
        free(config->test_name);
        free(config);
        return NULL;
    }
    return config;
}

void destroy_config(TestConfiguration *config) {
    if (config != NULL) {
        free(config->test_name);
        free(config->credential);
        free(config);
    }
}

int main() {
    TestConfiguration *config = create_config("UnitTest");
    if (config == NULL) {
        fprintf(stderr, "Failed to create config\n");
        return 1;
    }
    printf("Config created with credential: %s\n", config->credential);
    destroy_config(config);
    return 0;
}