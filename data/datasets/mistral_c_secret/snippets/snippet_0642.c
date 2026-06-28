#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_PASSWORD_ENV_VAR "DB_PASSWORD"

char* get_db_password() {
    char* password = getenv(DB_PASSWORD_ENV_VAR);
    if (password == NULL) {
        fprintf(stderr, "Error: Database password not found in environment variables.\n");
        exit(EXIT_FAILURE);
    }
    return password;
}

void connect_to_database() {
    char* password = get_db_password();
    printf("Connecting to database with password: %s\n", password);
    // Simulate database connection
}

int main() {
    connect_to_database();
    return 0;
}