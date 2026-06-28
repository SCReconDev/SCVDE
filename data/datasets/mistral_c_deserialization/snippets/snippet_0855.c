#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char state_name[50];
    int state_value;
} State;

int deserialize_state(const char* json_str, State* state) {
    struct json_object *parsed_json;
    struct json_object *state_name_obj, *state_value_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return -1;
    }

    if (!json_object_object_get_ex(parsed_json, "state_name", &state_name_obj)) {
        fprintf(stderr, "Error getting state_name\n");
        json_object_put(parsed_json);
        return -1;
    }

    if (!json_object_object_get_ex(parsed_json, "state_value", &state_value_obj)) {
        fprintf(stderr, "Error getting state_value\n");
        json_object_put(parsed_json);
        return -1;
    }

    strncpy(state->state_name, json_object_get_string(state_name_obj), sizeof(state->state_name) - 1);
    state->state_value = json_object_get_int(state_value_obj);

    json_object_put(parsed_json);
    return 0;
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    State state;

    printf("Enter state JSON: ");
    fgets(buffer, sizeof(buffer), stdin);

    if (deserialize_state(buffer, &state) == 0) {
        printf("Deserialized State: Name=%s, Value=%d\n", state.state_name, state.state_value);
    } else {
        fprintf(stderr, "Failed to deserialize state\n");
    }

    return 0;
}