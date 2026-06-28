#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* filename;
    char* content;
} FileData;

void import_file(const char* json_str, FileData* file_data) {
    struct json_object* parsed_json;
    struct json_object* filename;
    struct json_object* content;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "filename", &filename)) {
        fprintf(stderr, "Error: 'filename' field not found\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "content", &content)) {
        fprintf(stderr, "Error: 'content' field not found\n");
        json_object_put(parsed_json);
        return;
    }

    file_data->filename = strdup(json_object_get_string(filename));
    file_data->content = strdup(json_object_get_string(content));

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"filename\":\"example.txt\",\"content\":\"This is an example.\"}";
    FileData file_data;

    import_file(json_str, &file_data);

    printf("Filename: %s\n", file_data.filename);
    printf("Content: %s\n", file_data.content);

    free(file_data.filename);
    free(file_data.content);
    return 0;
}