#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* backup_name;
    char* backup_content;
} BackupData;

void deserialize_backup_data(const char* json_str, BackupData* backup_data) {
    cJSON* json = cJSON_Parse(json_str);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* backup_name = cJSON_GetObjectItemCaseSensitive(json, "backup_name");
    if (cJSON_IsString(backup_name) && (backup_name->valuestring != NULL)) {
        backup_data->backup_name = strdup(backup_name->valuestring);
    }

    cJSON* backup_content = cJSON_GetObjectItemCaseSensitive(json, "backup_content");
    if (cJSON_IsString(backup_content) && (backup_content->valuestring != NULL)) {
        backup_data->backup_content = strdup(backup_content->valuestring);
    }

    cJSON_Delete(json);
}

int main() {
    const char* json_str = "{\"backup_name\":\"backup_20230101\",\"backup_content\":\"Backup data for 2023-01-01.\"}";
    BackupData backup_data;

    deserialize_backup_data(json_str, &backup_data);

    printf("Backup Name: %s\n", backup_data.backup_name);
    printf("Backup Content: %s\n", backup_data.backup_content);

    free(backup_data.backup_name);
    free(backup_data.backup_content);

    return 0;
}