#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_PASSWORD "fake_db_password_67890"

int main() {
    char query[256];
    char result[1024];

    snprintf(query, sizeof(query), "SELECT * FROM users WHERE password='%s'", DB_PASSWORD);

    // Simulate database query
    printf("Executing query: %s\n", query);

    // Simulate result
    snprintf(result, sizeof(result), "{\"user\": \"admin\", \"password\": \"%s\"}", DB_PASSWORD);
    printf("Query Result: %s\n", result);

    return 0;
}