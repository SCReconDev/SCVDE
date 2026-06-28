#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *song_title;
    char *artist;
    int duration;
} Song;

void deserialize_song(const char *json_str, Song *song) {
    struct json_object *parsed_json;
    struct json_object *title_obj, *artist_obj, *duration_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "song_title", &title_obj);
    json_object_object_get_ex(parsed_json, "artist", &artist_obj);
    json_object_object_get_ex(parsed_json, "duration", &duration_obj);

    if (title_obj != NULL && json_object_get_type(title_obj) == json_type_string) {
        song->song_title = strdup(json_object_get_string(title_obj));
    }

    if (artist_obj != NULL && json_object_get_type(artist_obj) == json_type_string) {
        song->artist = strdup(json_object_get_string(artist_obj));
    }

    if (duration_obj != NULL && json_object_get_type(duration_obj) == json_type_int) {
        song->duration = json_object_get_int(duration_obj);
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"song_title\":\"Bohemian Rhapsody\",\"artist\":\"Queen\",\"duration\":354}";
    Song song;

    deserialize_song(json_str, &song);

    printf("Song Title: %s\n", song.song_title);
    printf("Artist: %s\n", song.artist);
    printf("Duration: %d seconds\n", song.duration);

    free(song.song_title);
    free(song.artist);
    return 0;
}