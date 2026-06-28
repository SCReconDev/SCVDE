#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_INPUT_SIZE 1024

typedef struct {
    char file_id[256];
    char file_name[256];
    char file_content[256];
} File;

int validate_file(File *file) {
    if (strlen(file->file_id) == 0 || strlen(file->file_name) == 0 || strlen(file->file_content) == 0) {
        return 0;
    }
    return 1;
}

File* deserialize_file(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *file_id_obj, *file_name_obj, *file_content_obj;
    File *file = malloc(sizeof(File));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        free(file);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "file_id", &file_id_obj);
    json_object_object_get_ex(parsed_json, "file_name", &file_name_obj);
    json_object_object_get_ex(parsed_json, "file_content", &file_content_obj);

    if (file_id_obj == NULL || file_name_obj == NULL || file_content_obj == NULL) {
        json_object_put(parsed_json);
        free(file);
        return NULL;
    }

    strncpy(file->file_id, json_object_get_string(file_id_obj), sizeof(file->file_id) - 1);
    strncpy(file->file_name, json_object_get_string(file_name_obj), sizeof(file->file_name) - 1);
    strncpy(file->file_content, json_object_get_string(file_content_obj), sizeof(file->file_content) - 1);

    json_object_put(parsed_json);

    if (!validate_file(file)) {
        free(file);
        return NULL;
    }

    return file;
}

void process_file(File *file) {
    printf("Processing file: %s, %s, %s\n", file->file_id, file->file_name, file->file_content);
}

int main() {
    char input[MAX_INPUT_SIZE];
    File *file;

    printf("Enter file data in JSON format: ");
    fgets(input, sizeof(input), stdin);

    file = deserialize_file(input);
    if (file == NULL) {
        printf("Invalid file data\n");
        return 1;
    }

    process_file(file);

    free(file);
    return 0;
}