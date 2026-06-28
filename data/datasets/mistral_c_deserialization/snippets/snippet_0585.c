#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* filename;
    char* content;
} FileData;

void deserialize_file_data(const char* json_str, FileData* file_data) {
    struct json_object* parsed_json;
    struct json_object* filename_obj;
    struct json_object* content_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "filename", &filename_obj);
    json_object_object_get_ex(parsed_json, "content", &content_obj);

    if (filename_obj != NULL && json_object_is_type(filename_obj, json_type_string)) {
        file_data->filename = strdup(json_object_get_string(filename_obj));
    }

    if (content_obj != NULL && json_object_is_type(content_obj, json_type_string)) {
        file_data->content = strdup(json_object_get_string(content_obj));
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"filename\":\"example.txt\",\"content\":\"Hello, World!\"}";
    FileData file_data;

    deserialize_file_data(json_str, &file_data);

    printf("Filename: %s\n", file_data.filename);
    printf("Content: %s\n", file_data.content);

    free(file_data.filename);
    free(file_data.content);
    return 0;
}