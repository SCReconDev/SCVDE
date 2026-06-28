#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* file_name;
    char* content;
} FileData;

void import_file(FileData* file) {
    printf("File Name: %s, Content: %s\n", file->file_name, file->content);
}

int main() {
    const char* state_file = "{\"file_name\":\"data.txt\",\"content\":\"Sample content\"}";
    struct json_object* json_obj = json_tokener_parse(state_file);

    if (json_obj == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    FileData file;
    json_object_object_foreach(json_obj, key, val) {
        if (strcmp(key, "file_name") == 0) {
            file.file_name = strdup(json_object_get_string(val));
        } else if (strcmp(key, "content") == 0) {
            file.content = strdup(json_object_get_string(val));
        }
    }

    import_file(&file);
    free(file.file_name);
    free(file.content);
    json_object_put(json_obj);

    return 0;
}