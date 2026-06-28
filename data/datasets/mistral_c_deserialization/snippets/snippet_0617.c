#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char restore_id[50];
    char restore_source[100];
    char restore_destination[100];
} Restore;

int validate_restore_json(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *restore_id_obj, *restore_source_obj, *restore_destination_obj;

    parsed_json = json_tokener_parse(json_str);
    if (!parsed_json) {
        return 0;
    }

    if (!json_object_object_get_ex(parsed_json, "restore_id", &restore_id_obj) ||
        !json_object_object_get_ex(parsed_json, "restore_source", &restore_source_obj) ||
        !json_object_object_get_ex(parsed_json, "restore_destination", &restore_destination_obj)) {
        json_object_put(parsed_json);
        return 0;
    }

    if (json_object_get_type(restore_id_obj) != json_type_string ||
        json_object_get_type(restore_source_obj) != json_type_string ||
        json_object_get_type(restore_destination_obj) != json_type_string) {
        json_object_put(parsed_json);
        return 0;
    }

    json_object_put(parsed_json);
    return 1;
}

Restore* deserialize_restore(const char *json_str) {
    Restore *restore = malloc(sizeof(Restore));
    if (!restore) {
        return NULL;
    }

    struct json_object *parsed_json;
    struct json_object *restore_id_obj, *restore_source_obj, *restore_destination_obj;

    parsed_json = json_tokener_parse(json_str);
    if (!parsed_json) {
        free(restore);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "restore_id", &restore_id_obj);
    json_object_object_get_ex(parsed_json, "restore_source", &restore_source_obj);
    json_object_object_get_ex(parsed_json, "restore_destination", &restore_destination_obj);

    strncpy(restore->restore_id, json_object_get_string(restore_id_obj), sizeof(restore->restore_id) - 1);
    strncpy(restore->restore_source, json_object_get_string(restore_source_obj), sizeof(restore->restore_source) - 1);
    strncpy(restore->restore_destination, json_object_get_string(restore_destination_obj), sizeof(restore->restore_destination) - 1);

    json_object_put(parsed_json);
    return restore;
}

void process_restore_data(const char *json_str) {
    if (!validate_restore_json(json_str)) {
        printf("Invalid restore data format\n");
        return;
    }

    Restore *restore = deserialize_restore(json_str);
    if (!restore) {
        printf("Failed to deserialize restore data\n");
        return;
    }

    printf("Restore ID: %s, Restore Source: %s, Restore Destination: %s\n", restore->restore_id, restore->restore_source, restore->restore_destination);
    free(restore);
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    printf("Enter restore data in JSON format:\n");
    fgets(buffer, sizeof(buffer), stdin);

    process_restore_data(buffer);

    return 0;
}