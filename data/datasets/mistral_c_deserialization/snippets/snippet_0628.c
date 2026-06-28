#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *name;
    char *category;
    float price;
} MenuItem;

void deserialize_menu_item(const char *json_str, MenuItem *item) {
    struct json_object *parsed_json;
    struct json_object *name;
    struct json_object *category;
    struct json_object *price;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "name", &name);
    json_object_object_get_ex(parsed_json, "category", &category);
    json_object_object_get_ex(parsed_json, "price", &price);

    if (name != NULL && json_object_is_type(name, json_type_string)) {
        item->name = strdup(json_object_get_string(name));
    } else {
        item->name = NULL;
    }

    if (category != NULL && json_object_is_type(category, json_type_string)) {
        item->category = strdup(json_object_get_string(category));
    } else {
        item->category = NULL;
    }

    if (price != NULL && json_object_is_type(price, json_type_double)) {
        item->price = json_object_get_double(price);
    } else {
        item->price = 0.0f;
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"name\":\"Margherita Pizza\",\"category\":\"Italian\",\"price\":12.99}";
    MenuItem item;

    deserialize_menu_item(json_str, &item);

    printf("Name: %s\n", item.name);
    printf("Category: %s\n", item.category);
    printf("Price: %.2f\n", item.price);

    free(item.name);
    free(item.category);
    return 0;
}