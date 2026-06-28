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
    struct json_object* filename;
    struct json_object* content;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "filename", &filename)) {
        file_data->filename = strdup(json_object_get_string(filename));
    }

    if (json_object_object_get_ex(parsed_json, "content", &content)) {
        file_data->content = strdup(json_object_get_string(content));
    }

    json_object_put(parsed_json);
}

void process_file_data(FileData* file_data) {
    printf("Filename: %s\n", file_data->filename);
    printf("Content: %s\n", file_data->content);
}

int main() {
    const char* json_str = "{\"filename\":\"example.txt\",\"content\":\"This is an example.\"}";
    FileData file_data;

    deserialize_file_data(json_str, &file_data);
    process_file_data(&file_data);

    free(file_data.filename);
    free(file_data.content);
    return 0;
}