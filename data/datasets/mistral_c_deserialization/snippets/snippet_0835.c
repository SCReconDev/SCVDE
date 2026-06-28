#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* filename;
    int size;
} FileInfo;

void deserialize_file_info(const char* json_str, FileInfo* file_info) {
    struct json_object* parsed_json;
    struct json_object* filename;
    struct json_object* size;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "filename", &filename);
    json_object_object_get_ex(parsed_json, "size", &size);

    if (filename != NULL && json_object_get_type(filename) == json_type_string) {
        file_info->filename = strdup(json_object_get_string(filename));
    }

    if (size != NULL && json_object_get_type(size) == json_type_int) {
        file_info->size = json_object_get_int(size);
    }

    json_object_put(parsed_json);
}

void import_file(const char* state_file) {
    FileInfo file_info = {NULL, 0};
    deserialize_file_info(state_file, &file_info);

    if (file_info.filename != NULL) {
        printf("Filename: %s\n", file_info.filename);
        free(file_info.filename);
    }

    printf("Size: %d\n", file_info.size);
}

int main() {
    const char* state_file = "{\"filename\":\"data.txt\",\"size\":1024}";
    import_file(state_file);
    return 0;
}