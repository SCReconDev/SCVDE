#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int value;
} State;

void deserialize_state(const char* data, State* state) {
    char* token = strtok((char*)data, "=");
    state->name = strdup(token);
    token = strtok(NULL, "=");
    state->value = atoi(token);
}

int main() {
    FILE* file = fopen("state_file.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char buffer[1024];
    fgets(buffer, sizeof(buffer), file);
    fclose(file);

    State state;
    deserialize_state(buffer, &state);

    printf("State Name: %s, Value: %d\n", state.name, state.value);
    free(state.name);

    return 0;
}