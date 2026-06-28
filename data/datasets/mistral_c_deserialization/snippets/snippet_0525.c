#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char state_name[MAX_BUFFER_SIZE];
    int state_value;
} State;

void import_state_file(const char* json_data) {
    struct json_object *parsed_json;
    struct json_object *state_name_obj, *state_value_obj;
    State state;

    parsed_json = json_tokener_parse(json_data);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON data\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "state_name", &state_name_obj) ||
        !json_object_object_get_ex(parsed_json, "state_value", &state_value_obj)) {
        fprintf(stderr, "Error: Missing required fields in JSON data\n");
        json_object_put(parsed_json);
        return;
    }

    strncpy(state.state_name, json_object_get_string(state_name_obj), MAX_BUFFER_SIZE - 1);
    state.state_value = json_object_get_int(state_value_obj);

    printf("State Name: %s, State Value: %d\n", state.state_name, state.state_value);

    json_object_put(parsed_json);
}

int main() {
    const char* json_data = "{\"state_name\":\"active\",\"state_value\":1}";
    import_state_file(json_data);
    return 0;
}