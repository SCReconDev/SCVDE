#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

typedef struct {
    char* file_name;
    char* content;
    int size;
} File;

bool validate_file_schema(cJSON* json) {
    if (!cJSON_HasObjectItem(json, "file_name") ||
        !cJSON_HasObjectItem(json, "content") ||
        !cJSON_HasObjectItem(json, "size")) {
        return false;
    }

    cJSON* file_name = cJSON_GetObjectItemCaseSensitive(json, "file_name");
    cJSON* content = cJSON_GetObjectItemCaseSensitive(json, "content");
    cJSON* size = cJSON_GetObjectItemCaseSensitive(json, "size");

    if (!cJSON_IsString(file_name) || !cJSON_IsString(content) || !cJSON_IsNumber(size)) {
        return false;
    }

    return true;
}

File* deserialize_file(const char* json_str) {
    cJSON* json = cJSON_Parse(json_str);
    if (!json) {
        return NULL;
    }

    if (!validate_file_schema(json)) {
        cJSON_Delete(json);
        return NULL;
    }

    File* file = (File*)malloc(sizeof(File));
    if (!file) {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON* file_name = cJSON_GetObjectItemCaseSensitive(json, "file_name");
    cJSON* content = cJSON_GetObjectItemCaseSensitive(json, "content");
    cJSON* size = cJSON_GetObjectItemCaseSensitive(json, "size");

    file->file_name = strdup(file_name->valuestring);
    file->content = strdup(content->valuestring);
    file->size = size->valueint;

    cJSON_Delete(json);

    return file;
}

void free_file(File* file) {
    if (file) {
        free(file->file_name);
        free(file->content);
        free(file);
    }
}

int main() {
    const char* json_str = "{\"file_name\":\"example.txt\",\"content\":\"This is an example file.\",\"size\":25}";
    File* file = deserialize_file(json_str);

    if (file) {
        printf("File Name: %s\n", file->file_name);
        printf("Content: %s\n", file->content);
        printf("Size: %d\n", file->size);
        free_file(file);
    } else {
        printf("Failed to deserialize file.\n");
    }

    return 0;
}