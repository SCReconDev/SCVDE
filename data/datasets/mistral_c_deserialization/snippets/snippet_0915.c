#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>

typedef struct {
    char* state_name;
    int state_value;
} State;

bool validate_state_json(const char* json_str) {
    struct json_object* obj = json_tokener_parse(json_str);
    if (obj == NULL) {
        return false;
    }

    bool has_state_name = json_object_object_get_ex(obj, "state_name", NULL);
    bool has_state_value = json_object_object_get_ex(obj, "state_value", NULL);

    json_object_put(obj);
    return has_state_name && has_state_value;
}

State* deserialize_state(const char* json_str) {
    if (!validate_state_json(json_str)) {
        return NULL;
    }

    struct json_object* obj = json_tokener_parse(json_str);
    State* state = malloc(sizeof(State));

    struct json_object* state_name_obj;
    json_object_object_get_ex(obj, "state_name", &state_name_obj);
    state->state_name = strdup(json_object_get_string(state_name_obj));

    struct json_object* state_value_obj;
    json_object_object_get_ex(obj, "state_value", &state_value_obj);
    state->state_value = json_object_get_int(state_value_obj);

    json_object_put(obj);
    return state;
}

void free_state(State* state) {
    free(state->state_name);
    free(state);
}

void import_state(const char* json_str) {
    State* state = deserialize_state(json_str);
    if (state == NULL) {
        printf("Invalid state data\n");
        return;
    }

    printf("State Name: %s, State Value: %d\n", state->state_name, state->state_value);
    free_state(state);
}

int main() {
    const char* json_str = "{\"state_name\":\"app_state\",\"state_value\":1}";
    import_state(json_str);
    return 0;
}