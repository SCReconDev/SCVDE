#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char state_name[50];
    int state_value;
} State;

void deserialize_state(State *state, const char *file_content) {
    sscanf(file_content, "%49s %d", state->state_name, &state->state_value);
}

void import_state(const char *file_content) {
    State state;
    deserialize_state(&state, file_content);
    printf("State Name: %s, State Value: %d\n", state.state_name, state.state_value);
}

int main() {
    char file_content[100];
    printf("Enter file content: ");
    fgets(file_content, sizeof(file_content), stdin);
    import_state(file_content);
    return 0;
}