#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *backup_name;
    char *data;
} BackupData;

void parse_backup_data(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *backup_name;
    struct json_object *data;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "backup_name", &backup_name)) {
        fprintf(stderr, "Backup name not found in JSON\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "data", &data)) {
        fprintf(stderr, "Data not found in JSON\n");
        json_object_put(parsed_json);
        return;
    }

    BackupData backup_data;
    backup_data.backup_name = strdup(json_object_get_string(backup_name));
    backup_data.data = strdup(json_object_get_string(data));

    printf("Backup Name: %s, Data: %s\n", backup_data.backup_name, backup_data.data);

    free(backup_data.backup_name);
    free(backup_data.data);
    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"backup_name\":\"config_backup\",\"data\":\"{\\\"theme\\\":\\\"dark\\\"}\"}";
    parse_backup_data(json_str);
    return 0;
}