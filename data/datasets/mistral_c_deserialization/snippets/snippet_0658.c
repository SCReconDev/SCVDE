#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *movie_title;
    char *director;
    int duration;
} Movie;

void deserialize_movie(const char *json_str, Movie *movie) {
    struct json_object *parsed_json;
    struct json_object *title_obj, *director_obj, *duration_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "movie_title", &title_obj);
    json_object_object_get_ex(parsed_json, "director", &director_obj);
    json_object_object_get_ex(parsed_json, "duration", &duration_obj);

    if (title_obj != NULL && json_object_get_type(title_obj) == json_type_string) {
        movie->movie_title = strdup(json_object_get_string(title_obj));
    }

    if (director_obj != NULL && json_object_get_type(director_obj) == json_type_string) {
        movie->director = strdup(json_object_get_string(director_obj));
    }

    if (duration_obj != NULL && json_object_get_type(duration_obj) == json_type_int) {
        movie->duration = json_object_get_int(duration_obj);
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"movie_title\":\"Inception\",\"director\":\"Christopher Nolan\",\"duration\":148}";
    Movie movie;

    deserialize_movie(json_str, &movie);

    printf("Movie Title: %s\n", movie.movie_title);
    printf("Director: %s\n", movie.director);
    printf("Duration: %d minutes\n", movie.duration);

    free(movie.movie_title);
    free(movie.director);
    return 0;
}