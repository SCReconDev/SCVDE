#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *file_name;
    char *content;
} FileData;

void parse_file_data(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *file_name;
    struct json_object *content;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "file_name", &file_name)) {
        fprintf(stderr, "File name not found in JSON\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "content", &content)) {
        fprintf(stderr, "Content not found in JSON\n");
        json_object_put(parsed_json);
        return;
    }

    FileData file_data;
    file_data.file_name = strdup(json_object_get_string(file_name));
    file_data.content = strdup(json_object_get_string(content));

    printf("File Name: %s, Content: %s\n", file_data.file_name, file_data.content);

    free(file_data.file_name);
    free(file_data.content);
    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"file_name\":\"config.json\",\"content\":\"{\\\"theme\\\":\\\"dark\\\"}\"}";
    parse_file_data(json_str);
    return 0;
}