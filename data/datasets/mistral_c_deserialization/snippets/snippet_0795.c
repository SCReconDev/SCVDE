#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *filename;
    char *content;
} FileData;

void save_file(FileData *file) {
    printf("Saving file: %s\n", file->filename);
    printf("Content: %s\n", file->content);
}

int main() {
    const char *state_file = "{\"filename\":\"config.json\",\"content\":\"{\\\"theme\\\":\\\"dark\\\"}\"}";
    struct json_object *parsed_json;
    struct json_object *filename;
    struct json_object *content;
    FileData file;

    parsed_json = json_tokener_parse(state_file);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    json_object_object_get_ex(parsed_json, "filename", &filename);
    json_object_object_get_ex(parsed_json, "content", &content);

    if (filename == NULL || content == NULL) {
        fprintf(stderr, "Missing required fields in JSON\n");
        json_object_put(parsed_json);
        return 1;
    }

    file.filename = strdup(json_object_get_string(filename));
    file.content = strdup(json_object_get_string(content));

    save_file(&file);

    free(file.filename);
    free(file.content);
    json_object_put(parsed_json);

    return 0;
}