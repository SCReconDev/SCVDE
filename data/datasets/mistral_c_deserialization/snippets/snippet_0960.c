#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *preference_name;
    char *preference_value;
} Preference;

void import_preferences(const char *file_path, Preference *preferences, int *count) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Error allocating memory\n");
        fclose(file);
        return;
    }

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    struct json_object *parsed_json;
    struct json_object *preferences_array;
    size_t i;

    parsed_json = json_tokener_parse(buffer);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        free(buffer);
        return;
    }

    if (json_object_object_get_ex(parsed_json, "preferences", &preferences_array)) {
        *count = json_object_array_length(preferences_array);
        for (i = 0; i < *count; i++) {
            struct json_object *preference_obj = json_object_array_get_idx(preferences_array, i);
            struct json_object *name_obj;
            struct json_object *value_obj;

            if (json_object_object_get_ex(preference_obj, "name", &name_obj)) {
                preferences[i].preference_name = strdup(json_object_get_string(name_obj));
            }

            if (json_object_object_get_ex(preference_obj, "value", &value_obj)) {
                preferences[i].preference_value = strdup(json_object_get_string(value_obj));
            }
        }
    }

    json_object_put(parsed_json);
    free(buffer);
}

int main() {
    const char *file_path = "preferences.json";
    Preference preferences[10];
    int count = 0;
    int i;

    import_preferences(file_path, preferences, &count);

    for (i = 0; i < count; i++) {
        printf("Preference Name: %s, Preference Value: %s\n", preferences[i].preference_name, preferences[i].preference_value);
        free(preferences[i].preference_name);
        free(preferences[i].preference_value);
    }

    return 0;
}