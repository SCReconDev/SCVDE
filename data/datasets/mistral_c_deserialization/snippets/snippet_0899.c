#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char song[50];
    char artist[50];
    int duration;
} Song;

int validate_song_schema(json_object *jobj) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "song") == 0 && !json_object_is_type(val, json_type_string)) {
            return 0;
        }
        if (strcmp(key, "artist") == 0 && !json_object_is_type(val, json_type_string)) {
            return 0;
        }
        if (strcmp(key, "duration") == 0 && !json_object_is_type(val, json_type_int)) {
            return 0;
        }
    }
    return 1;
}

Song* deserialize_song(const char *json_str) {
    json_object *jobj = json_tokener_parse(json_str);
    if (!jobj) {
        return NULL;
    }

    if (!validate_song_schema(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Song *song = (Song*)malloc(sizeof(Song));
    if (!song) {
        json_object_put(jobj);
        return NULL;
    }

    json_object *jsong = json_object_object_get(jobj, "song");
    json_object *jartist = json_object_object_get(jobj, "artist");
    json_object *jduration = json_object_object_get(jobj, "duration");

    strcpy(song->song, json_object_get_string(jsong));
    strcpy(song->artist, json_object_get_string(jartist));
    song->duration = json_object_get_int(jduration);

    json_object_put(jobj);
    return song;
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    printf("Enter JSON string: ");
    fgets(buffer, MAX_BUFFER_SIZE, stdin);

    Song *song = deserialize_song(buffer);
    if (song) {
        printf("Song: %s, Artist: %s, Duration: %d\n", song->song, song->artist, song->duration);
        free(song);
    } else {
        printf("Invalid JSON or schema\n");
    }

    return 0;
}