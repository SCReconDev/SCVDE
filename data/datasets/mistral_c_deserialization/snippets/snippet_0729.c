#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *game_title;
    char *developer;
    int release_year;
} Game;

void deserialize_game(const char *json_str, Game *game) {
    struct json_object *parsed_json;
    struct json_object *game_title;
    struct json_object *developer;
    struct json_object *release_year;

    parsed_json = json_tokener_parse(json_str);
    if (json_object_object_get_ex(parsed_json, "game_title", &game_title)) {
        game->game_title = strdup(json_object_get_string(game_title));
    }
    if (json_object_object_get_ex(parsed_json, "developer", &developer)) {
        game->developer = strdup(json_object_get_string(developer));
    }
    if (json_object_object_get_ex(parsed_json, "release_year", &release_year)) {
        game->release_year = json_object_get_int(release_year);
    }
    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"game_title\":\"Sample Game\",\"developer\":\"Game Studio\",\"release_year\":2023}";
    Game game;

    deserialize_game(json_str, &game);

    printf("Game Title: %s\n", game.game_title);
    printf("Developer: %s\n", game.developer);
    printf("Release Year: %d\n", game.release_year);

    free(game.game_title);
    free(game.developer);
    return 0;
}