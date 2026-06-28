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

void restore_state(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        char data[100];
        fgets(data, sizeof(data), file);
        FileState state;
        load_file_state(&state, data);
        printf("Restored State: %s = %s\n", state.name, state.state);
        fclose(file);
    }
}

int main() {
    char filename[50];
    printf("Enter filename to restore: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;
    restore_state(filename);
    return 0;
}