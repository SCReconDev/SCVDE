#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char game[50];
    char platform[50];
    int year;
} Game;

int validate_game_schema(json_object *jobj) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "game") == 0 && !json_object_is_type(val, json_type_string)) {
            return 0;
        }
        if (strcmp(key, "platform") == 0 && !json_object_is_type(val, json_type_string)) {
            return 0;
        }
        if (strcmp(key, "year") == 0 && !json_object_is_type(val, json_type_int)) {
            return 0;
        }
    }
    return 1;
}

Game* deserialize_game(const char *json_str) {
    json_object *jobj = json_tokener_parse(json_str);
    if (!jobj) {
        return NULL;
    }

    if (!validate_game_schema(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Game *game = (Game*)malloc(sizeof(Game));
    if (!game) {
        json_object_put(jobj);
        return NULL;
    }

    json_object *jgame = json_object_object_get(jobj, "game");
    json_object *jplatform = json_object_object_get(jobj, "platform");
    json_object *jyear = json_object_object_get(jobj, "year");

    strcpy(game->game, json_object_get_string(jgame));
    strcpy(game->platform, json_object_get_string(jplatform));
    game->year = json_object_get_int(jyear);

    json_object_put(jobj);
    return game;
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    printf("Enter JSON string: ");
    fgets(buffer, MAX_BUFFER_SIZE, stdin);

    Game *game = deserialize_game(buffer);
    if (game) {
        printf("Game: %s, Platform: %s, Year: %d\n", game->game, game->platform, game->year);
        free(game);
    } else {
        printf("Invalid JSON or schema\n");
    }

    return 0;
}