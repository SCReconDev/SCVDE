#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* file_name;
    char* content;
} FileData;

void process_file_data(FileData* data) {
    printf("File Name: %s, Content: %s\n", data->file_name, data->content);
}

int main() {
    const char* state_file = "{\"file_name\":\"state.json\",\"content\":\"{\\\"status\\\":\\\"active\\\",\\\"timestamp\\\":\\\"2023-10-01T12:00:00Z\\\"}\"}";
    struct json_object* parsed_json;
    struct json_object* file_name_obj;
    struct json_object* content_obj;
    FileData data;

    parsed_json = json_tokener_parse(state_file);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    if (!json_object_object_get_ex(parsed_json, "file_name", &file_name_obj) ||
        !json_object_object_get_ex(parsed_json, "content", &content_obj)) {
        fprintf(stderr, "Error extracting JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    data.file_name = strdup(json_object_get_string(file_name_obj));
    data.content = strdup(json_object_get_string(content_obj));

    process_file_data(&data);

    free(data.file_name);
    free(data.content);
    json_object_put(parsed_json);

    return 0;
}