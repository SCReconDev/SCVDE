#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *db_host;
    int db_port;
    char *db_user;
    char *db_password;
} TestConfiguration;

TestConfiguration* create_test_configuration(const char *db_host, int db_port, const char *db_user) {
    TestConfiguration *config = (TestConfiguration*)malloc(sizeof(TestConfiguration));
    if (config == NULL) {
        return NULL;
    }

    config->db_host = strdup(db_host);
    if (config->db_host == NULL) {
        free(config);
        return NULL;
    }

    config->db_port = db_port;

    config->db_user = strdup(db_user);
    if (config->db_user == NULL) {
        free(config->db_host);
        free(config);
        return NULL;
    }

    config->db_password = getenv("DB_PASSWORD");
    if (config->db_password == NULL) {
        free(config->db_user);
        free(config->db_host);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_test_configuration(TestConfiguration *config) {
    if (config != NULL) {
        if (config->db_password != NULL) {
            free(config->db_password);
        }
        if (config->db_user != NULL) {
            free(config->db_user);
        }
        if (config->db_host != NULL) {
            free(config->db_host);
        }
        free(config);
    }
}

int main() {
    TestConfiguration *config = create_test_configuration("localhost", 3306, "testuser");
    if (config == NULL) {
        fprintf(stderr, "Failed to create test configuration\n");
        return 1;
    }

    printf("Test configuration created with DB host: %s\n", config->db_host);
    printf("Test configuration created with DB port: %d\n", config->db_port);
    printf("Test configuration created with DB user: %s\n", config->db_user);

    destroy_test_configuration(config);
    return 0;
}