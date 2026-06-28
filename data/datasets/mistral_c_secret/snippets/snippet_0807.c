#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CREDENTIAL_LENGTH 100

typedef struct {
    char credential[MAX_CREDENTIAL_LENGTH];
} TestConfiguration;

TestConfiguration* create_test_configuration() {
    TestConfiguration* config = (TestConfiguration*)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    const char* credential_env = getenv("TEST_CREDENTIAL");
    if (credential_env == NULL) {
        fprintf(stderr, "TEST_CREDENTIAL environment variable not set\n");
        free(config);
        return NULL;
    }

    strncpy(config->credential, credential_env, MAX_CREDENTIAL_LENGTH - 1);
    config->credential[MAX_CREDENTIAL_LENGTH - 1] = '\0';

    return config;
}

void run_test(TestConfiguration* config, const char* test_name) {
    printf("Running test %s with credential: %s\n", test_name, config->credential);
}

void destroy_test_configuration(TestConfiguration* config) {
    if (config != NULL) {
        free(config);
    }
}

int main() {
    TestConfiguration* config = create_test_configuration();
    if (config == NULL) {
        return 1;
    }

    run_test(config, "test_name");
    destroy_test_configuration(config);

    return 0;
}