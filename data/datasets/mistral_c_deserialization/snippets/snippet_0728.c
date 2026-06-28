#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *movie_title;
    char *director;
    int release_year;
} Movie;

void deserialize_movie(const char *json_str, Movie *movie) {
    struct json_object *parsed_json;
    struct json_object *movie_title;
    struct json_object *director;
    struct json_object *release_year;

    parsed_json = json_tokener_parse(json_str);
    if (json_object_object_get_ex(parsed_json, "movie_title", &movie_title)) {
        movie->movie_title = strdup(json_object_get_string(movie_title));
    }
    if (json_object_object_get_ex(parsed_json, "director", &director)) {
        movie->director = strdup(json_object_get_string(director));
    }
    if (json_object_object_get_ex(parsed_json, "release_year", &release_year)) {
        movie->release_year = json_object_get_int(release_year);
    }
    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"movie_title\":\"Sample Movie\",\"director\":\"Jane Doe\",\"release_year\":2023}";
    Movie movie;

    deserialize_movie(json_str, &movie);

    printf("Movie Title: %s\n", movie.movie_title);
    printf("Director: %s\n", movie.director);
    printf("Release Year: %d\n", movie.release_year);

    free(movie.movie_title);
    free(movie.director);
    return 0;
}