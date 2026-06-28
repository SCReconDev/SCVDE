#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CONFIG_FILE "test_config.json"

typedef struct {
    char *credential;
    char *file;
} TestConfiguration;

TestConfiguration* create_config() {
    TestConfiguration *config = (TestConfiguration*)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->credential = getenv("TEST_CREDENTIAL");
    if (config->credential == NULL) {
        fprintf(stderr, "TEST_CREDENTIAL environment variable not set.\n");
        free(config);
        return NULL;
    }

    config->file = strdup(TEST_CONFIG_FILE);
    if (config->file == NULL) {
        free(config);
        return NULL;
    }

    return config;
}

void destroy_config(TestConfiguration *config) {
    if (config != NULL) {
        free(config->file);
        free(config);
    }
}

int main() {
    TestConfiguration *config = create_config();
    if (config == NULL) {
        return 1;
    }

    printf("Test configuration created with credential: %s\n", config->credential);
    destroy_config(config);
    return 0;
}