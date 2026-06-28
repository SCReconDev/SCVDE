#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_FILE_SIZE 1024

typedef struct {
    char restore_id[256];
    int restore_value;
    char restore_data[256];
} Restore;

void deserialize_restore(Restore *restore, const char *file_content) {
    struct json_object *parsed_json;
    struct json_object *restore_id_obj, *restore_value_obj, *restore_data_obj;

    parsed_json = json_tokener_parse(file_content);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON file content\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "restore_id", &restore_id_obj);
    json_object_object_get_ex(parsed_json, "restore_value", &restore_value_obj);
    json_object_object_get_ex(parsed_json, "restore_data", &restore_data_obj);

    if (restore_id_obj != NULL && json_object_is_type(restore_id_obj, json_type_string)) {
        strncpy(restore->restore_id, json_object_get_string(restore_id_obj), sizeof(restore->restore_id) - 1);
    }

    if (restore_value_obj != NULL && json_object_is_type(restore_value_obj, json_type_int)) {
        restore->restore_value = json_object_get_int(restore_value_obj);
    }

    if (restore_data_obj != NULL && json_object_is_type(restore_data_obj, json_type_string)) {
        strncpy(restore->restore_data, json_object_get_string(restore_data_obj), sizeof(restore->restore_data) - 1);
    }

    json_object_put(parsed_json);
}

int main() {
    Restore restore;
    char file_content[MAX_FILE_SIZE];
    FILE *file;
    char filename[256];

    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;

    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    fread(file_content, sizeof(char), sizeof(file_content), file);
    fclose(file);

    deserialize_restore(&restore, file_content);

    printf("Deserialized Restore:\n");
    printf("Restore ID: %s\n", restore.restore_id);
    printf("Restore Value: %d\n", restore.restore_value);
    printf("Restore Data: %s\n", restore.restore_data);

    return 0;
}