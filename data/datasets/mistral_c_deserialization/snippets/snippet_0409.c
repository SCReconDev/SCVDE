#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int value;
} State;

void restore_state(const char* file_content, State* state) {
    char* token = strtok((char*)file_content, ",");
    state->name = strdup(token);
    token = strtok(NULL, ",");
    state->value = atoi(token);
}

int main() {
    char* file_content = "backup_state,100";
    State state;
    restore_state(file_content, &state);
    printf("Name: %s, Value: %d\n", state.name, state.value);
    free(state.name);
    return 0;
}