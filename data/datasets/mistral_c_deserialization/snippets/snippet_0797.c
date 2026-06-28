#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *database;
    char *table;
} RestoreConfig;

void restore_data(RestoreConfig *config) {
    printf("Restoring data from database: %s\n", config->database);
    printf("Table: %s\n", config->table);
}

int main() {
    const char *input_file = "{\"database\":\"main_db\",\"table\":\"users\"}";
    struct json_object *parsed_json;
    struct json_object *database;
    struct json_object *table;
    RestoreConfig config;

    parsed_json = json_tokener_parse(input_file);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    json_object_object_get_ex(parsed_json, "database", &database);
    json_object_object_get_ex(parsed_json, "table", &table);

    if (database == NULL || table == NULL) {
        fprintf(stderr, "Missing required fields in JSON\n");
        json_object_put(parsed_json);
        return 1;
    }

    config.database = strdup(json_object_get_string(database));
    config.table = strdup(json_object_get_string(table));

    restore_data(&config);

    free(config.database);
    free(config.table);
    json_object_put(parsed_json);

    return 0;
}