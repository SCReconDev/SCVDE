#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *state_name;
    int state_value;
} State;

void import_state(const char *file_path, State *states, int *count) {
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
    struct json_object *states_array;
    size_t i;

    parsed_json = json_tokener_parse(buffer);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        free(buffer);
        return;
    }

    if (json_object_object_get_ex(parsed_json, "states", &states_array)) {
        *count = json_object_array_length(states_array);
        for (i = 0; i < *count; i++) {
            struct json_object *state_obj = json_object_array_get_idx(states_array, i);
            struct json_object *name_obj;
            struct json_object *value_obj;

            if (json_object_object_get_ex(state_obj, "name", &name_obj)) {
                states[i].state_name = strdup(json_object_get_string(name_obj));
            }

            if (json_object_object_get_ex(state_obj, "value", &value_obj)) {
                states[i].state_value = json_object_get_int(value_obj);
            }
        }
    }

    json_object_put(parsed_json);
    free(buffer);
}

int main() {
    const char *file_path = "state.json";
    State states[10];
    int count = 0;
    int i;

    import_state(file_path, states, &count);

    for (i = 0; i < count; i++) {
        printf("State Name: %s, State Value: %d\n", states[i].state_name, states[i].state_value);
        free(states[i].state_name);
    }

    return 0;
}