#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* restaurant_name;
    char* cuisine;
    int rating;
} Restaurant;

void deserialize_restaurant(const char* json_str, Restaurant* restaurant) {
    struct json_object* parsed_json;
    struct json_object* restaurant_name;
    struct json_object* cuisine;
    struct json_object* rating;

    parsed_json = json_tokener_parse(json_str);

    if (json_object_object_get_ex(parsed_json, "restaurant_name", &restaurant_name)) {
        restaurant->restaurant_name = strdup(json_object_get_string(restaurant_name));
    }

    if (json_object_object_get_ex(parsed_json, "cuisine", &cuisine)) {
        restaurant->cuisine = strdup(json_object_get_string(cuisine));
    }

    if (json_object_object_get_ex(parsed_json, "rating", &rating)) {
        restaurant->rating = json_object_get_int(rating);
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"restaurant_name\":\"The Italian Bistro\",\"cuisine\":\"Italian\",\"rating\":5}";
    Restaurant restaurant;

    deserialize_restaurant(json_str, &restaurant);

    printf("Restaurant Name: %s\n", restaurant.restaurant_name);
    printf("Cuisine: %s\n", restaurant.cuisine);
    printf("Rating: %d\n", restaurant.rating);

    free(restaurant.restaurant_name);
    free(restaurant.cuisine);

    return 0;
}