#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char name[50];
    char description[200];
    int rating;
} Movie;

void print_movie(Movie *movie) {
    printf("Name: %s\n", movie->name);
    printf("Description: %s\n", movie->description);
    printf("Rating: %d\n", movie->rating);
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    FILE *file = fopen("movie.json", "r");
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

    struct json_object *name_obj, *description_obj, *rating_obj;
    if (!json_object_object_get_ex(parsed_json, "name", &name_obj) ||
        !json_object_object_get_ex(parsed_json, "description", &description_obj) ||
        !json_object_object_get_ex(parsed_json, "rating", &rating_obj)) {
        fprintf(stderr, "Error accessing JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    Movie movie;
    strncpy(movie.name, json_object_get_string(name_obj), sizeof(movie.name) - 1);
    strncpy(movie.description, json_object_get_string(description_obj), sizeof(movie.description) - 1);
    movie.rating = json_object_get_int(rating_obj);

    print_movie(&movie);

    json_object_put(parsed_json);
    return 0;
}