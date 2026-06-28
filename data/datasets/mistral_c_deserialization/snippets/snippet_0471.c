#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int score;
} Player;

void load_player(Player* player, const char* data) {
    char* token = strtok((char*)data, ":");
    player->name = strdup(token);
    token = strtok(NULL, ":");
    player->score = atoi(token);
}

int main() {
    char* data = "Player1:100";
    Player player;
    load_player(&player, data);
    printf("Player: %s, Score: %d\n", player.name, player.score);
    free(player.name);
    return 0;
}