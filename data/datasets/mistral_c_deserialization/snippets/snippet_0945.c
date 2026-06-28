#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* file_name;
    char* file_content;
} FileData;

void parse_uploaded_file(const char* file_data) {
    cJSON* json = cJSON_Parse(file_data);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* file_name = cJSON_GetObjectItemCaseSensitive(json, "file_name");
    cJSON* file_content = cJSON_GetObjectItemCaseSensitive(json, "file_content");

    if (cJSON_IsString(file_name) && (file_name->valuestring != NULL)) {
        printf("File Name: %s\n", file_name->valuestring);
    }

    if (cJSON_IsString(file_content) && (file_content->valuestring != NULL)) {
        printf("File Content: %s\n", file_content->valuestring);
    }

    cJSON_Delete(json);
}

int main() {
    const char* file_data = "{\"file_name\":\"example.txt\",\"file_content\":\"This is an example file.\"}";
    parse_uploaded_file(file_data);
    return 0;
}