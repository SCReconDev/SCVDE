#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* file_name;
    char* file_content;
} File;

void deserialize_file(const char* json_str, File* file) {
    struct json_object* parsed_json;
    struct json_object* file_name;
    struct json_object* file_content;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "file_name", &file_name);
    json_object_object_get_ex(parsed_json, "file_content", &file_content);

    if (file_name != NULL && json_object_is_type(file_name, json_type_string)) {
        file->file_name = strdup(json_object_get_string(file_name));
    }

    if (file_content != NULL && json_object_is_type(file_content, json_type_string)) {
        file->file_content = strdup(json_object_get_string(file_content));
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"file_name\":\"example.txt\",\"file_content\":\"This is an example file.\"}";
    File file;

    deserialize_file(json_str, &file);

    printf("File Name: %s\n", file.file_name);
    printf("File Content: %s\n", file.file_content);

    free(file.file_name);
    free(file.file_content);
    return 0;
}