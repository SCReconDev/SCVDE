#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_FILE_SIZE 8192

typedef struct {
    char name[50];
    int value;
} StateItem;

void import_state_file(const char *file_path) {
    FILE *file;
    char buffer[MAX_FILE_SIZE];
    struct json_object *parsed_json;
    struct json_object *items_array;
    size_t i, array_length;
    StateItem item;

    file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return;
    }

    fread(buffer, 1, sizeof(buffer), file);
    fclose(file);

    parsed_json = json_tokener_parse(buffer);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing state file\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "items", &items_array)) {
        fprintf(stderr, "Invalid state file format\n");
        json_object_put(parsed_json);
        return;
    }

    array_length = json_object_array_length(items_array);
    for (i = 0; i < array_length; i++) {
        struct json_object *item_obj = json_object_array_get_idx(items_array, i);
        struct json_object *name_obj, *value_obj;

        if (!json_object_object_get_ex(item_obj, "name", &name_obj) ||
            !json_object_object_get_ex(item_obj, "value", &value_obj)) {
            continue;
        }

        strncpy(item.name, json_object_get_string(name_obj), sizeof(item.name) - 1);
        item.value = json_object_get_int(value_obj);

        printf("State Item - Name: %s, Value: %d\n", item.name, item.value);
    }

    json_object_put(parsed_json);
}

int main() {
    char file_path[256];
    printf("Enter file path: ");
    fgets(file_path, sizeof(file_path), stdin);
    file_path[strcspn(file_path, "\n")] = 0; // Remove newline character

    import_state_file(file_path);

    return 0;
}