#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* file_name;
    char* file_data;
} FileData;

void deserialize_file_data(const char* json_str, FileData* file_data) {
    struct json_object* parsed_json;
    struct json_object* file_name;
    struct json_object* file_data_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "file_name", &file_name);
    json_object_object_get_ex(parsed_json, "file_data", &file_data_obj);

    if (file_name != NULL && file_data_obj != NULL) {
        file_data->file_name = strdup(json_object_get_string(file_name));
        file_data->file_data = strdup(json_object_get_string(file_data_obj));
    } else {
        fprintf(stderr, "Invalid JSON format\n");
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"file_name\":\"data.txt\",\"file_data\":\"file_content\"}";
    FileData file_data;

    deserialize_file_data(json_str, &file_data);

    printf("File Name: %s\n", file_data.file_name);
    printf("File Data: %s\n", file_data.file_data);

    free(file_data.file_name);
    free(file_data.file_data);

    return 0;
}