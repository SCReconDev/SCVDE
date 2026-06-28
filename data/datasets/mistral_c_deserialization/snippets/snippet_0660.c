#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *game_title;
    char *platform;
    int release_year;
} Game;

void deserialize_game(const char *json_str, Game *game) {
    struct json_object *parsed_json;
    struct json_object *title_obj, *platform_obj, *year_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "game_title", &title_obj);
    json_object_object_get_ex(parsed_json, "platform", &platform_obj);
    json_object_object_get_ex(parsed_json, "release_year", &year_obj);

    if (title_obj != NULL && json_object_get_type(title_obj) == json_type_string) {
        game->game_title = strdup(json_object_get_string(title_obj));
    }

    if (platform_obj != NULL && json_object_get_type(platform_obj) == json_type_string) {
        game->platform = strdup(json_object_get_string(platform_obj));
    }

    if (year_obj != NULL && json_object_get_type(year_obj) == json_type_int) {
        game->release_year = json_object_get_int(year_obj);
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"game_title\":\"The Legend of Zelda: Breath of the Wild\",\"platform\":\"Nintendo Switch\",\"release_year\":2017}";
    Game game;

    deserialize_game(json_str, &game);

    printf("Game Title: %s\n", game.game_title);
    printf("Platform: %s\n", game.platform);
    printf("Release Year: %d\n", game.release_year);

    free(game.game_title);
    free(game.platform);
    return 0;
}