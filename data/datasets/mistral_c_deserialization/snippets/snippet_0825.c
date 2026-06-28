#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *filename;
    int size;
} FileInfo;

void parse_file_info(json_object *jobj, FileInfo *info) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "filename") == 0) {
            info->filename = strdup(json_object_get_string(val));
        } else if (strcmp(key, "size") == 0) {
            info->size = json_object_get_int(val);
        }
    }
}

int main() {
    const char *state_file = "{\"filename\":\"data.txt\",\"size\":1024}";
    json_object *jobj = json_tokener_parse(state_file);

    if (jobj == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    FileInfo info;
    parse_file_info(jobj, &info);

    printf("Filename: %s\n", info.filename);
    printf("Size: %d\n", info.size);

    free(info.filename);
    json_object_put(jobj);

    return 0;
}