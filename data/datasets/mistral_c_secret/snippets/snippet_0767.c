#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_DB_HOST "localhost"
#define TEST_DB_USER "testuser"
#define TEST_DB_NAME "testdb"
#define TEST_DB_PASS_ENV "TEST_DB_PASSWORD"

typedef struct {
    char *host;
    char *user;
    char *password;
    char *dbname;
} TestConfiguration;

TestConfiguration* create_test_configuration() {
    TestConfiguration *config = (TestConfiguration*)malloc(sizeof(TestConfiguration));
    config->host = strdup(TEST_DB_HOST);
    config->user = strdup(TEST_DB_USER);
    config->dbname = strdup(TEST_DB_NAME);
    config->password = getenv(TEST_DB_PASS_ENV);
    if (config->password == NULL) {
        fprintf(stderr, "Error: Test database password not found in environment variables.\n");
        free(config->host);
        free(config->user);
        free(config->dbname);
        free(config);
        return NULL;
    }
    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        free(config->host);
        free(config->user);
        free(config->password);
        free(config->dbname);
        free(config);
    }
}

int run_test(TestConfiguration *config) {
    if (config == NULL || config->password == NULL) {
        return -1;
    }
    printf("Running test on database %s at %s with user %s and password %s\n",
           config->dbname, config->host, config->user, config->password);
    return 0;
}

int main() {
    TestConfiguration *config = create_test_configuration();
    if (config == NULL) {
        return 1;
    }
    run_test(config);
    destroy_test_configuration(config);
    return 0;
}