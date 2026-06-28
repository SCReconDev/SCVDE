#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int level;
} GameState;

void deserialize_game_state(GameState* state, const char* data) {
    char* token = strtok((char*)data, ",");
    state->name = strdup(token);
    token = strtok(NULL, ",");
    state->level = atoi(token);
}

void import_game_state(const char* file_data) {
    GameState state;
    deserialize_game_state(&state, file_data);
    printf("Game State - Name: %s, Level: %d\n", state.name, state.level);
    free(state.name);
}

int main() {
    const char* file_data = "Player1,5";
    import_game_state(file_data);
    return 0;
}