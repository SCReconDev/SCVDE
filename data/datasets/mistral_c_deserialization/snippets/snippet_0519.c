#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char name[50];
    char genre[50];
    int year;
} Album;

void print_album(Album *album) {
    printf("Name: %s\n", album->name);
    printf("Genre: %s\n", album->genre);
    printf("Year: %d\n", album->year);
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    FILE *file = fopen("album.json", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fread(buffer, sizeof(char), MAX_BUFFER_SIZE, file);
    fclose(file);

    struct json_object *parsed_json = json_tokener_parse(buffer);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    struct json_object *name_obj, *genre_obj, *year_obj;
    if (!json_object_object_get_ex(parsed_json, "name", &name_obj) ||
        !json_object_object_get_ex(parsed_json, "genre", &genre_obj) ||
        !json_object_object_get_ex(parsed_json, "year", &year_obj)) {
        fprintf(stderr, "Error accessing JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    Album album;
    strncpy(album.name, json_object_get_string(name_obj), sizeof(album.name) - 1);
    strncpy(album.genre, json_object_get_string(genre_obj), sizeof(album.genre) - 1);
    album.year = json_object_get_int(year_obj);

    print_album(&album);

    json_object_put(parsed_json);
    return 0;
}