#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* file_name;
    char* file_content;
} FileData;

void deserialize_file_data(const char* json_str, FileData* file_data) {
    cJSON* json = cJSON_Parse(json_str);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* file_name = cJSON_GetObjectItemCaseSensitive(json, "file_name");
    if (cJSON_IsString(file_name) && (file_name->valuestring != NULL)) {
        file_data->file_name = strdup(file_name->valuestring);
    }

    cJSON* file_content = cJSON_GetObjectItemCaseSensitive(json, "file_content");
    if (cJSON_IsString(file_content) && (file_content->valuestring != NULL)) {
        file_data->file_content = strdup(file_content->valuestring);
    }

    cJSON_Delete(json);
}

int main() {
    const char* json_str = "{\"file_name\":\"example.txt\",\"file_content\":\"This is an example file.\"}";
    FileData file_data;

    deserialize_file_data(json_str, &file_data);

    printf("File Name: %s\n", file_data.file_name);
    printf("File Content: %s\n", file_data.file_content);

    free(file_data.file_name);
    free(file_data.file_content);

    return 0;
}