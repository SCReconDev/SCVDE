#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* state_id;
    char* state_value;
} State;

void process_state(State* state) {
    printf("State ID: %s\n", state->state_id);
    printf("State Value: %s\n", state->state_value);
}

State* deserialize_state(const char* json_str) {
    struct json_object* parsed_json;
    struct json_object* state_id_obj;
    struct json_object* state_value_obj;
    State* state = malloc(sizeof(State));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        free(state);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "state_id", &state_id_obj);
    json_object_object_get_ex(parsed_json, "state_value", &state_value_obj);

    if (state_id_obj == NULL || state_value_obj == NULL) {
        fprintf(stderr, "Invalid JSON format\n");
        json_object_put(parsed_json);
        free(state);
        return NULL;
    }

    state->state_id = strdup(json_object_get_string(state_id_obj));
    state->state_value = strdup(json_object_get_string(state_value_obj));

    json_object_put(parsed_json);
    return state;
}

int main() {
    const char* json_str = "{\"state_id\":\"state123\",\"state_value\":\"active\"}";
    State* state = deserialize_state(json_str);

    if (state != NULL) {
        process_state(state);
        free(state->state_id);
        free(state->state_value);
        free(state);
    }

    return 0;
}