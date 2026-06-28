#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char name[50];
    char cuisine[50];
    int rating;
} Restaurant;

void show_restaurant(Restaurant *restaurant) {
    printf("Name: %s\n", restaurant->name);
    printf("Cuisine: %s\n", restaurant->cuisine);
    printf("Rating: %d\n", restaurant->rating);
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    FILE *file = fopen("restaurant.json", "r");
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

    struct json_object *name_obj, *cuisine_obj, *rating_obj;
    if (!json_object_object_get_ex(parsed_json, "name", &name_obj) ||
        !json_object_object_get_ex(parsed_json, "cuisine", &cuisine_obj) ||
        !json_object_object_get_ex(parsed_json, "rating", &rating_obj)) {
        fprintf(stderr, "Error accessing JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    Restaurant restaurant;
    strncpy(restaurant.name, json_object_get_string(name_obj), sizeof(restaurant.name) - 1);
    strncpy(restaurant.cuisine, json_object_get_string(cuisine_obj), sizeof(restaurant.cuisine) - 1);
    restaurant.rating = json_object_get_int(rating_obj);

    show_restaurant(&restaurant);

    json_object_put(parsed_json);
    return 0;
}