#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char file_id[50];
    char file_name[50];
    char file_path[100];
} FileInfo;

int validate_file_info(FileInfo *file_info) {
    if (strlen(file_info->file_id) == 0 || strlen(file_info->file_name) == 0 || strlen(file_info->file_path) == 0) {
        return 0;
    }
    return 1;
}

FileInfo* deserialize_file_info(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *file_id_obj, *file_name_obj, *file_path_obj;
    FileInfo *file_info = (FileInfo*)malloc(sizeof(FileInfo));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        free(file_info);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "file_id", &file_id_obj);
    json_object_object_get_ex(parsed_json, "file_name", &file_name_obj);
    json_object_object_get_ex(parsed_json, "file_path", &file_path_obj);

    if (file_id_obj == NULL || file_name_obj == NULL || file_path_obj == NULL) {
        json_object_put(parsed_json);
        free(file_info);
        return NULL;
    }

    strncpy(file_info->file_id, json_object_get_string(file_id_obj), sizeof(file_info->file_id) - 1);
    strncpy(file_info->file_name, json_object_get_string(file_name_obj), sizeof(file_info->file_name) - 1);
    strncpy(file_info->file_path, json_object_get_string(file_path_obj), sizeof(file_info->file_path) - 1);

    json_object_put(parsed_json);

    if (!validate_file_info(file_info)) {
        free(file_info);
        return NULL;
    }

    return file_info;
}

void process_file_info(FileInfo *file_info) {
    printf("File ID: %s\n", file_info->file_id);
    printf("File Name: %s\n", file_info->file_name);
    printf("File Path: %s\n", file_info->file_path);
}

int main() {
    char json_str[MAX_BUFFER_SIZE];
    FileInfo *file_info;

    printf("Enter file info data in JSON format:\n");
    fgets(json_str, MAX_BUFFER_SIZE, stdin);

    file_info = deserialize_file_info(json_str);
    if (file_info == NULL) {
        printf("Invalid file info data\n");
        return 1;
    }

    process_file_info(file_info);
    free(file_info);

    return 0;
}