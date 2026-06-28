#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *music_title;
    char *artist;
    int release_year;
} Music;

void deserialize_music(const char *json_str, Music *music) {
    struct json_object *parsed_json;
    struct json_object *music_title;
    struct json_object *artist;
    struct json_object *release_year;

    parsed_json = json_tokener_parse(json_str);
    if (json_object_object_get_ex(parsed_json, "music_title", &music_title)) {
        music->music_title = strdup(json_object_get_string(music_title));
    }
    if (json_object_object_get_ex(parsed_json, "artist", &artist)) {
        music->artist = strdup(json_object_get_string(artist));
    }
    if (json_object_object_get_ex(parsed_json, "release_year", &release_year)) {
        music->release_year = json_object_get_int(release_year);
    }
    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"music_title\":\"Sample Music\",\"artist\":\"Music Artist\",\"release_year\":2023}";
    Music music;

    deserialize_music(json_str, &music);

    printf("Music Title: %s\n", music.music_title);
    printf("Artist: %s\n", music.artist);
    printf("Release Year: %d\n", music.release_year);

    free(music.music_title);
    free(music.artist);
    return 0;
}