#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* file_name;
    char* content;
} FileData;

void parse_uploaded_file(const char* file_content) {
    struct json_object* parsed_json;
    struct json_object* file_name;
    struct json_object* content;

    parsed_json = json_tokener_parse(file_content);

    if (json_object_object_get_ex(parsed_json, "file_name", &file_name)) {
        FileData* file_data = (FileData*)malloc(sizeof(FileData));
        file_data->file_name = strdup(json_object_get_string(file_name));

        if (json_object_object_get_ex(parsed_json, "content", &content)) {
            file_data->content = strdup(json_object_get_string(content));
        } else {
            file_data->content = strdup("");
        }

        printf("File Name: %s, Content: %s\n", file_data->file_name, file_data->content);
        free(file_data->file_name);
        free(file_data->content);
        free(file_data);
    }

    json_object_put(parsed_json);
}

int main() {
    const char* file_content = "{\"file_name\":\"example.txt\",\"content\":\"This is a test file.\"}";
    parse_uploaded_file(file_content);
    return 0;
}