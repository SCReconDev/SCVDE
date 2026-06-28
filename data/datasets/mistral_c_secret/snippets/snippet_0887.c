#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *db_host;
    char *db_user;
    char *db_password;
    char *db_name;
} TestConfig;

TestConfig* create_test_config(const char *db_host, const char *db_user, const char *db_name) {
    TestConfig *config = (TestConfig*)malloc(sizeof(TestConfig));
    if (config == NULL) {
        return NULL;
    }
    config->db_host = strdup(db_host);
    config->db_user = strdup(db_user);
    config->db_name = strdup(db_name);
    config->db_password = getenv("TEST_DB_PASSWORD");
    if (config->db_password == NULL) {
        fprintf(stderr, "TEST_DB_PASSWORD environment variable not set\n");
        free(config->db_host);
        free(config->db_user);
        free(config->db_name);
        free(config);
        return NULL;
    }
    return config;
}

void destroy_test_config(TestConfig *config) {
    if (config != NULL) {
        free(config->db_host);
        free(config->db_user);
        free(config->db_name);
        free(config);
    }
}

void run_test(TestConfig *config) {
    printf("Running test with configuration:\n");
    printf("DB Host: %s\n", config->db_host);
    printf("DB User: %s\n", config->db_user);
    printf("DB Name: %s\n", config->db_name);
    printf("DB Password: %s\n", config->db_password);
}

int main() {
    TestConfig *config = create_test_config("localhost", "test_user", "test_db");
    if (config == NULL) {
        return 1;
    }

    run_test(config);

    destroy_test_config(config);
    return 0;
}