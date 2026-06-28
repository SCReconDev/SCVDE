#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int value;
} State;

void import_state(const char* file_data, State* state) {
    char* data = strdup(file_data);
    char* token = strtok(data, "=");
    state->name = strdup(token);
    token = strtok(NULL, "=");
    state->value = atoi(token);
    free(data);
}

int main() {
    char* file_data = "counter=42";
    State state;
    import_state(file_data, &state);
    printf("State Name: %s, State Value: %d\n", state.name, state.value);
    free(state.name);
    return 0;
}