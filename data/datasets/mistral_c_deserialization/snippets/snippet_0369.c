#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[256];
    int value;
} State;

void deserialize_state(State *state, const char *data) {
    sscanf(data, "%255[^;];%d", state->name, &state->value);
}

void restore_state(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    char buffer[512];
    fgets(buffer, sizeof(buffer), file);
    fclose(file);
    State state;
    deserialize_state(&state, buffer);
    printf("State: %s = %d\n", state.name, state.value);
}

int main() {
    char file_path[256];
    printf("Enter file path: ");
    fgets(file_path, sizeof(file_path), stdin);
    file_path[strcspn(file_path, "\n")] = 0;
    restore_state(file_path);
    return 0;
}