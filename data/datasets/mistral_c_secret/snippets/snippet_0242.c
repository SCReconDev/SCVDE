#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_PASSWORD "fake_db_password_1234567890"

typedef struct {
    char* host;
    int port;
    char* user;
    char* password;
} DatabaseConfig;

void connect_to_database(DatabaseConfig* config) {
    printf("Connecting to database at %s:%d with user %s and password %s\n",
           config->host, config->port, config->user, config->password);
}

int main() {
    DatabaseConfig config = {
        .host = "localhost",
        .port = 5432,
        .user = "admin",
        .password = DB_PASSWORD
    };
    connect_to_database(&config);
    return 0;
}