#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_USERNAME "admin"
#define DB_PASSWORD "admin_password_123"

typedef struct {
    char *db_host;
    char *db_name;
    char *db_username;
    char *db_password;
} TestConfiguration;

TestConfiguration* create_test_configuration(const char *db_host, const char *db_name) {
    TestConfiguration *config = (TestConfiguration*)malloc(sizeof(TestConfiguration));
    config->db_host = strdup(db_host);
    config->db_name = strdup(db_name);
    config->db_username = strdup(DB_USERNAME);
    config->db_password = strdup(DB_PASSWORD);
    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    free(config->db_host);
    free(config->db_name);
    free(config->db_username);
    free(config->db_password);
    free(config);
}

int main() {
    TestConfiguration *config = create_test_configuration("localhost", "test_db");
    printf("Test configuration created with credentials: %s/%s\n", config->db_username, config->db_password);
    destroy_test_configuration(config);
    return 0;
}