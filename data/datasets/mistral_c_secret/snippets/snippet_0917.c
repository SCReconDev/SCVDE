#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *db_host;
    int db_port;
    char *db_user;
    char *db_password;
    char *test_data;
} TestConfig;

TestConfig* create_test_config(const char *db_host, int db_port, const char *db_user, const char *db_password, const char *test_data) {
    TestConfig *config = (TestConfig*)malloc(sizeof(TestConfig));
    config->db_host = strdup(db_host);
    config->db_port = db_port;
    config->db_user = strdup(db_user);
    config->db_password = strdup(db_password);
    config->test_data = strdup(test_data);
    return config;
}

void destroy_test_config(TestConfig *config) {
    free(config->db_host);
    free(config->db_user);
    free(config->db_password);
    free(config->test_data);
    free(config);
}

void run_test(TestConfig *config) {
    printf("Running test with data: %s\n", config->test_data);
    printf("Using database at %s:%d\n", config->db_host, config->db_port);
    printf("Using credentials: %s:%s\n", config->db_user, config->db_password);
}

int main() {
    const char *test_db_password = getenv("TEST_DB_PASSWORD");
    if (test_db_password == NULL) {
        fprintf(stderr, "TEST_DB_PASSWORD environment variable not set\n");
        return 1;
    }

    TestConfig *config = create_test_config("localhost", 5432, "test_user", test_db_password, "test_data");
    run_test(config);
    destroy_test_config(config);

    return 0;
}