#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* filename;
    char* content;
} FileData;

void import_file(FileData* file_data) {
    printf("Importing file: %s with content: %s\n", file_data->filename, file_data->content);
}

int main() {
    const char* state_file = "{\"filename\":\"config.txt\",\"content\":\"settings\"}";
    cJSON* json = cJSON_Parse(state_file);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return EXIT_FAILURE;
    }

    FileData file_data;
    cJSON* filename = cJSON_GetObjectItemCaseSensitive(json, "filename");
    if (cJSON_IsString(filename) && (filename->valuestring != NULL)) {
        file_data.filename = strdup(filename->valuestring);
    } else {
        fprintf(stderr, "Invalid filename in state file\n");
        cJSON_Delete(json);
        return EXIT_FAILURE;
    }

    cJSON* content = cJSON_GetObjectItemCaseSensitive(json, "content");
    if (cJSON_IsString(content) && (content->valuestring != NULL)) {
        file_data.content = strdup(content->valuestring);
    } else {
        fprintf(stderr, "Invalid content in state file\n");
        free(file_data.filename);
        cJSON_Delete(json);
        return EXIT_FAILURE;
    }

    import_file(&file_data);
    free(file_data.filename);
    free(file_data.content);
    cJSON_Delete(json);
    return EXIT_SUCCESS;
}