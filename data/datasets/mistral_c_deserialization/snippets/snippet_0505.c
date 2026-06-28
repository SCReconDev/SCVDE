#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* filename;
    int size;
} FileInfo;

void import_file(const char* state_file) {
    cJSON* json = cJSON_Parse(state_file);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* filename = cJSON_GetObjectItemCaseSensitive(json, "filename");
    cJSON* size = cJSON_GetObjectItemCaseSensitive(json, "size");

    if (cJSON_IsString(filename) && (filename->valuestring != NULL) && cJSON_IsNumber(size)) {
        FileInfo info;
        info.filename = strdup(filename->valuestring);
        info.size = size->valueint;

        printf("File: %s, Size: %d\n", info.filename, info.size);

        free(info.filename);
    }

    cJSON_Delete(json);
}

int main() {
    const char* state_file = "{\"filename\":\"data.txt\",\"size\":1024}";
    import_file(state_file);
    return 0;
}