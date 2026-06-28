#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *filename;
    int size;
} FileInfo;

void deserialize_file_info(const char *json_str, FileInfo *info) {
    struct json_object *parsed_json;
    struct json_object *filename;
    struct json_object *size;

    parsed_json = json_tokener_parse(json_str);

    if (json_object_object_get_ex(parsed_json, "filename", &filename)) {
        info->filename = strdup(json_object_get_string(filename));
    }

    if (json_object_object_get_ex(parsed_json, "size", &size)) {
        info->size = json_object_get_int(size);
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"filename\":\"document.txt\",\"size\":1024}";
    FileInfo info;

    deserialize_file_info(json_str, &info);

    printf("Filename: %s\n", info.filename);
    printf("Size: %d\n", info.size);

    free(info.filename);

    return 0;
}