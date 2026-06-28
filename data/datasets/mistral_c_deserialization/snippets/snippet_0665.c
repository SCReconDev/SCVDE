#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char filename[MAX_BUFFER_SIZE];
    char content[MAX_BUFFER_SIZE];
} FileData;

void import_file_data(const char *json_str, FileData *file_data) {
    struct json_object *parsed_json;
    struct json_object *filename_obj;
    struct json_object *content_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "filename", &filename_obj);
    if (filename_obj != NULL) {
        strncpy(file_data->filename, json_object_get_string(filename_obj), MAX_BUFFER_SIZE - 1);
    }

    json_object_object_get_ex(parsed_json, "content", &content_obj);
    if (content_obj != NULL) {
        strncpy(file_data->content, json_object_get_string(content_obj), MAX_BUFFER_SIZE - 1);
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"filename\":\"example.txt\",\"content\":\"Hello, World!\"}";
    FileData file_data;

    import_file_data(json_str, &file_data);

    printf("Filename: %s\n", file_data.filename);
    printf("Content: %s\n", file_data.content);

    return 0;
}