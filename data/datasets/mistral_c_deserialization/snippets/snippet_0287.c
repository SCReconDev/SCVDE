#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    char state[50];
} FileState;

void load_file_state(FileState *state, const char *data) {
    sscanf(data, "%49s %49s", state->name, state->state);
}

void import_file_state(const char *data) {
    FileState state;
    load_file_state(&state, data);
    printf("File State: %s = %s\n", state.name, state.state);
}

int main() {
    char data[100];
    printf("Enter file state data: ");
    fgets(data, sizeof(data), stdin);
    import_file_state(data);
    return 0;
}