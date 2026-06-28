#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* database;
    char* table;
} RestoreCommand;

void execute_restore(RestoreCommand* command) {
    printf("Restoring database: %s table: %s\n", command->database, command->table);
}

int main() {
    const char* input_file = "{\"database\":\"main\",\"table\":\"users\"}";
    cJSON* json = cJSON_Parse(input_file);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return EXIT_FAILURE;
    }

    RestoreCommand command;
    cJSON* database = cJSON_GetObjectItemCaseSensitive(json, "database");
    if (cJSON_IsString(database) && (database->valuestring != NULL)) {
        command.database = strdup(database->valuestring);
    } else {
        fprintf(stderr, "Invalid database in input file\n");
        cJSON_Delete(json);
        return EXIT_FAILURE;
    }

    cJSON* table = cJSON_GetObjectItemCaseSensitive(json, "table");
    if (cJSON_IsString(table) && (table->valuestring != NULL)) {
        command.table = strdup(table->valuestring);
    } else {
        fprintf(stderr, "Invalid table in input file\n");
        free(command.database);
        cJSON_Delete(json);
        return EXIT_FAILURE;
    }

    execute_restore(&command);
    free(command.database);
    free(command.table);
    cJSON_Delete(json);
    return EXIT_SUCCESS;
}