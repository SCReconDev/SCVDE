#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_FILE_SIZE 8192

typedef struct {
    char pref_name[50];
    char pref_value[100];
} UserPreference;

void import_user_preferences(const char *file_path) {
    FILE *file;
    char buffer[MAX_FILE_SIZE];
    struct json_object *parsed_json;
    struct json_object *prefs_array;
    size_t i, array_length;
    UserPreference pref;

    file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return;
    }

    fread(buffer, 1, sizeof(buffer), file);
    fclose(file);

    parsed_json = json_tokener_parse(buffer);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing preferences file\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "preferences", &prefs_array)) {
        fprintf(stderr, "Invalid preferences format\n");
        json_object_put(parsed_json);
        return;
    }

    array_length = json_object_array_length(prefs_array);
    for (i = 0; i < array_length; i++) {
        struct json_object *pref_obj = json_object_array_get_idx(prefs_array, i);
        struct json_object *name_obj, *value_obj;

        if (!json_object_object_get_ex(pref_obj, "name", &name_obj) ||
            !json_object_object_get_ex(pref_obj, "value", &value_obj)) {
            continue;
        }

        strncpy(pref.pref_name, json_object_get_string(name_obj), sizeof(pref.pref_name) - 1);
        strncpy(pref.pref_value, json_object_get_string(value_obj), sizeof(pref.pref_value) - 1);

        printf("Preference - Name: %s, Value: %s\n", pref.pref_name, pref.pref_value);
    }

    json_object_put(parsed_json);
}

int main() {
    char file_path[256];
    printf("Enter file path: ");
    fgets(file_path, sizeof(file_path), stdin);
    file_path[strcspn(file_path, "\n")] = 0; // Remove newline character

    import_user_preferences(file_path);

    return 0;
}