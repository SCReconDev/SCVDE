#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* backup_name;
    char* backup_path;
} BackupData;

void deserialize_backup_data(const char* json_str, BackupData* backup_data) {
    struct json_object* parsed_json;
    struct json_object* backup_name;
    struct json_object* backup_path;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "backup_name", &backup_name)) {
        backup_data->backup_name = strdup(json_object_get_string(backup_name));
    }

    if (json_object_object_get_ex(parsed_json, "backup_path", &backup_path)) {
        backup_data->backup_path = strdup(json_object_get_string(backup_path));
    }

    json_object_put(parsed_json);
}

void process_backup_data(BackupData* backup_data) {
    printf("Backup Name: %s\n", backup_data->backup_name);
    printf("Backup Path: %s\n", backup_data->backup_path);
}

int main() {
    const char* json_str = "{\"backup_name\":\"daily_backup\",\"backup_path\":\"/backups/daily\"}";
    BackupData backup_data;

    deserialize_backup_data(json_str, &backup_data);
    process_backup_data(&backup_data);

    free(backup_data.backup_name);
    free(backup_data.backup_path);
    return 0;
}