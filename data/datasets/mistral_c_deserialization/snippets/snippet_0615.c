#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char file_id[50];
    char file_name[100];
    char file_content[500];
} File;

int validate_file_json(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *file_id_obj, *file_name_obj, *file_content_obj;

    parsed_json = json_tokener_parse(json_str);
    if (!parsed_json) {
        return 0;
    }

    if (!json_object_object_get_ex(parsed_json, "file_id", &file_id_obj) ||
        !json_object_object_get_ex(parsed_json, "file_name", &file_name_obj) ||
        !json_object_object_get_ex(parsed_json, "file_content", &file_content_obj)) {
        json_object_put(parsed_json);
        return 0;
    }

    if (json_object_get_type(file_id_obj) != json_type_string ||
        json_object_get_type(file_name_obj) != json_type_string ||
        json_object_get_type(file_content_obj) != json_type_string) {
        json_object_put(parsed_json);
        return 0;
    }

    json_object_put(parsed_json);
    return 1;
}

File* deserialize_file(const char *json_str) {
    File *file = malloc(sizeof(File));
    if (!file) {
        return NULL;
    }

    struct json_object *parsed_json;
    struct json_object *file_id_obj, *file_name_obj, *file_content_obj;

    parsed_json = json_tokener_parse(json_str);
    if (!parsed_json) {
        free(file);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "file_id", &file_id_obj);
    json_object_object_get_ex(parsed_json, "file_name", &file_name_obj);
    json_object_object_get_ex(parsed_json, "file_content", &file_content_obj);

    strncpy(file->file_id, json_object_get_string(file_id_obj), sizeof(file->file_id) - 1);
    strncpy(file->file_name, json_object_get_string(file_name_obj), sizeof(file->file_name) - 1);
    strncpy(file->file_content, json_object_get_string(file_content_obj), sizeof(file->file_content) - 1);

    json_object_put(parsed_json);
    return file;
}

void process_file_data(const char *json_str) {
    if (!validate_file_json(json_str)) {
        printf("Invalid file data format\n");
        return;
    }

    File *file = deserialize_file(json_str);
    if (!file) {
        printf("Failed to deserialize file data\n");
        return;
    }

    printf("File ID: %s, File Name: %s, File Content: %s\n", file->file_id, file->file_name, file->file_content);
    free(file);
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    printf("Enter file data in JSON format:\n");
    fgets(buffer, sizeof(buffer), stdin);

    process_file_data(buffer);

    return 0;
}