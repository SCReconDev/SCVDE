#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_DB_HOST "localhost"
#define TEST_DB_USER "test_user"
#define TEST_DB_NAME "test_db"
#define TEST_DB_PASSWORD_ENV_VAR "TEST_DB_PASSWORD"

typedef struct {
    char* host;
    char* user;
    char* password;
    char* dbname;
} TestConfiguration;

TestConfiguration* create_test_configuration() {
    TestConfiguration* config = (TestConfiguration*)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->host = strdup(TEST_DB_HOST);
    config->user = strdup(TEST_DB_USER);
    config->dbname = strdup(TEST_DB_NAME);

    if (config->host == NULL || config->user == NULL || config->dbname == NULL) {
        free(config->host);
        free(config->user);
        free(config->dbname);
        free(config);
        return NULL;
    }

    config->password = getenv(TEST_DB_PASSWORD_ENV_VAR);
    if (config->password == NULL) {
        free(config->host);
        free(config->user);
        free(config->dbname);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_configuration(TestConfiguration* config) {
    if (config != NULL) {
        free(config->host);
        free(config->user);
        free(config->password);
        free(config->dbname);
        free(config);
    }
}

int main() {
    TestConfiguration* config = create_test_configuration();
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration\n");
        return 1;
    }

    printf("Test Configuration created successfully\n");
    printf("Host: %s\n", config->host);
    printf("User: %s\n", config->user);
    printf("Password: %s\n", config->password);
    printf("Database: %s\n", config->dbname);

    destroy_test_configuration(config);
    return 0;
}