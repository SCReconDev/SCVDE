#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *host;
    int port;
    char *user;
    char *password;
} DBConnector;

DBConnector *create_db_connector(const char *host, int port, const char *user, const char *env_var) {
    DBConnector *connector = (DBConnector *)malloc(sizeof(DBConnector));
    connector->host = strdup(host);
    connector->port = port;
    connector->user = strdup(user);
    connector->password = getenv(env_var);
    if (connector->password == NULL) {
        fprintf(stderr, "Error: Environment variable not set\n");
        exit(EXIT_FAILURE);
    }
    return connector;
}

void destroy_db_connector(DBConnector *connector) {
    free(connector->host);
    free(connector->user);
    free(connector);
}

int main() {
    const char *host = "localhost";
    int port = 5432;
    const char *user = "postgres";
    const char *env_var = "DB_PASSWORD";
    DBConnector *connector = create_db_connector(host, port, user, env_var);
    printf("DB Connector created for host: %s, port: %d, user: %s\n", connector->host, connector->port, connector->user);
    destroy_db_connector(connector);
    return 0;
}