#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *name;
    char *description;
    float rating;
} Movie;

void deserialize_movie(const char *json_str, Movie *movie) {
    struct json_object *parsed_json;
    struct json_object *name;
    struct json_object *description;
    struct json_object *rating;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "name", &name);
    json_object_object_get_ex(parsed_json, "description", &description);
    json_object_object_get_ex(parsed_json, "rating", &rating);

    if (name != NULL && json_object_is_type(name, json_type_string)) {
        movie->name = strdup(json_object_get_string(name));
    } else {
        movie->name = NULL;
    }

    if (description != NULL && json_object_is_type(description, json_type_string)) {
        movie->description = strdup(json_object_get_string(description));
    } else {
        movie->description = NULL;
    }

    if (rating != NULL && json_object_is_type(rating, json_type_double)) {
        movie->rating = json_object_get_double(rating);
    } else {
        movie->rating = 0.0f;
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"name\":\"Inception\",\"description\":\"A mind-bending thriller\",\"rating\":8.8}";
    Movie movie;

    deserialize_movie(json_str, &movie);

    printf("Name: %s\n", movie.name);
    printf("Description: %s\n", movie.description);
    printf("Rating: %.1f\n", movie.rating);

    free(movie.name);
    free(movie.description);
    return 0;
}