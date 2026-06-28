#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *name;
    char *genre;
    int duration;
} Song;

void deserialize_song(const char *json_str, Song *song) {
    struct json_object *parsed_json;
    struct json_object *name;
    struct json_object *genre;
    struct json_object *duration;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "name", &name);
    json_object_object_get_ex(parsed_json, "genre", &genre);
    json_object_object_get_ex(parsed_json, "duration", &duration);

    if (name != NULL && json_object_is_type(name, json_type_string)) {
        song->name = strdup(json_object_get_string(name));
    } else {
        song->name = NULL;
    }

    if (genre != NULL && json_object_is_type(genre, json_type_string)) {
        song->genre = strdup(json_object_get_string(genre));
    } else {
        song->genre = NULL;
    }

    if (duration != NULL && json_object_is_type(duration, json_type_int)) {
        song->duration = json_object_get_int(duration);
    } else {
        song->duration = 0;
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"name\":\"Bohemian Rhapsody\",\"genre\":\"Rock\",\"duration\":354}";
    Song song;

    deserialize_song(json_str, &song);

    printf("Name: %s\n", song.name);
    printf("Genre: %s\n", song.genre);
    printf("Duration: %d seconds\n", song.duration);

    free(song.name);
    free(song.genre);
    return 0;
}