#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PASSWORD_LENGTH 100

char* get_db_password() {
    char* password = getenv("DB_PASSWORD");
    if (password == NULL) {
        fprintf(stderr, "DB_PASSWORD environment variable not set.\n");
        exit(EXIT_FAILURE);
    }
    return strdup(password);
}

void connect_to_database(char* password) {
    printf("Connecting to database with password: %s\n", password);
    // Simulate database connection
}

int main() {
    char* password = get_db_password();
    connect_to_database(password);
    free(password);
    return 0;
}