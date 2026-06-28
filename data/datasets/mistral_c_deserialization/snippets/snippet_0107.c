#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char* state;
} FileState;

void import_state(FileState* state, const char* file_content) {
    char* token = strdup(file_content);
    char* part = strtok(token, "|");
    state->id = atoi(part);
    part = strtok(NULL, "|");
    state->state = strdup(part);
    free(token);
}

int main() {
    char* file_content = "456|Imported state data";
    FileState state;
    import_state(&state, file_content);
    printf("ID: %d, State: %s\n", state.id, state.state);
    return 0;
}