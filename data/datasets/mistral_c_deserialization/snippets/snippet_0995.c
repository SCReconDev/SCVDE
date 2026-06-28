#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_FILE_SIZE 1024

typedef struct {
    char state_id[256];
    int state_value;
    char state_data[256];
} State;

void deserialize_state(State *state, const char *file_content) {
    struct json_object *parsed_json;
    struct json_object *state_id_obj, *state_value_obj, *state_data_obj;

    parsed_json = json_tokener_parse(file_content);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON file content\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "state_id", &state_id_obj);
    json_object_object_get_ex(parsed_json, "state_value", &state_value_obj);
    json_object_object_get_ex(parsed_json, "state_data", &state_data_obj);

    if (state_id_obj != NULL && json_object_is_type(state_id_obj, json_type_string)) {
        strncpy(state->state_id, json_object_get_string(state_id_obj), sizeof(state->state_id) - 1);
    }

    if (state_value_obj != NULL && json_object_is_type(state_value_obj, json_type_int)) {
        state->state_value = json_object_get_int(state_value_obj);
    }

    if (state_data_obj != NULL && json_object_is_type(state_data_obj, json_type_string)) {
        strncpy(state->state_data, json_object_get_string(state_data_obj), sizeof(state->state_data) - 1);
    }

    json_object_put(parsed_json);
}

int main() {
    State state;
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

    deserialize_state(&state, file_content);

    printf("Deserialized State:\n");
    printf("State ID: %s\n", state.state_id);
    printf("State Value: %d\n", state.state_value);
    printf("State Data: %s\n", state.state_data);

    return 0;
}