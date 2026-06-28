#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char movie[50];
    char director[50];
    int year;
} Movie;

int validate_movie_schema(json_object *jobj) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "movie") == 0 && !json_object_is_type(val, json_type_string)) {
            return 0;
        }
        if (strcmp(key, "director") == 0 && !json_object_is_type(val, json_type_string)) {
            return 0;
        }
        if (strcmp(key, "year") == 0 && !json_object_is_type(val, json_type_int)) {
            return 0;
        }
    }
    return 1;
}

Movie* deserialize_movie(const char *json_str) {
    json_object *jobj = json_tokener_parse(json_str);
    if (!jobj) {
        return NULL;
    }

    if (!validate_movie_schema(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Movie *movie = (Movie*)malloc(sizeof(Movie));
    if (!movie) {
        json_object_put(jobj);
        return NULL;
    }

    json_object *jmovie = json_object_object_get(jobj, "movie");
    json_object *jdirector = json_object_object_get(jobj, "director");
    json_object *jyear = json_object_object_get(jobj, "year");

    strcpy(movie->movie, json_object_get_string(jmovie));
    strcpy(movie->director, json_object_get_string(jdirector));
    movie->year = json_object_get_int(jyear);

    json_object_put(jobj);
    return movie;
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    printf("Enter JSON string: ");
    fgets(buffer, MAX_BUFFER_SIZE, stdin);

    Movie *movie = deserialize_movie(buffer);
    if (movie) {
        printf("Movie: %s, Director: %s, Year: %d\n", movie->movie, movie->director, movie->year);
        free(movie);
    } else {
        printf("Invalid JSON or schema\n");
    }

    return 0;
}