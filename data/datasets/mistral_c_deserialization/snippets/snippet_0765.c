#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* file_name;
    char* file_content;
} FileData;

void deserialize_file_data(const char* json_str, FileData* file_data) {
    struct json_object* parsed_json;
    struct json_object* file_name_obj;
    struct json_object* file_content_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "file_name", &file_name_obj)) {
        fprintf(stderr, "Error getting file_name from JSON\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "file_content", &file_content_obj)) {
        fprintf(stderr, "Error getting file_content from JSON\n");
        json_object_put(parsed_json);
        return;
    }

    file_data->file_name = strdup(json_object_get_string(file_name_obj));
    file_data->file_content = strdup(json_object_get_string(file_content_obj));

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"file_name\":\"example.txt\",\"file_content\":\"This is an example file.\"}";
    FileData file_data;

    deserialize_file_data(json_str, &file_data);

    printf("File Name: %s\n", file_data.file_name);
    printf("File Content: %s\n", file_data.file_content);

    free(file_data.file_name);
    free(file_data.file_content);

    return 0;
}