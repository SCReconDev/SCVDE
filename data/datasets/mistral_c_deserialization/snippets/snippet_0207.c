#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char filename[50];
    char content[100];
} FileState;

void deserialize_file_state(FileState *state, const char *data) {
    sscanf(data, "%49s %99[^\n]", state->filename, state->content);
}

void import_file_state(const char *data) {
    FileState state;
    deserialize_file_state(&state, data);
    printf("File State: %s = %s\n", state.filename, state.content);
}

int main() {
    char data[200];
    printf("Enter file state data: ");
    fgets(data, sizeof(data), stdin);
    import_file_state(data);
    return 0;
}