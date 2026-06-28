#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* data;
} State;

void deserialize_state(const char* file_data, State* state) {
    char* token = strtok((char*)file_data, ";");
    state->name = strdup(token);
    token = strtok(NULL, ";");
    state->data = strdup(token);
}

void import_state(const char* state_file) {
    State state;
    deserialize_state(state_file, &state);
    printf("State Name: %s, State Data: %s\n", state.name, state.data);
    free(state.name);
    free(state.data);
}

int main() {
    const char* state_file = "app_state;dark_mode=true";
    import_state(state_file);
    return 0;
}