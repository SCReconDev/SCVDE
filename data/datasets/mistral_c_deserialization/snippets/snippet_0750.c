#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* product_name;
    char* category;
    float price;
} Product;

void deserialize_product(const char* json_str, Product* product) {
    struct json_object* parsed_json;
    struct json_object* product_name;
    struct json_object* category;
    struct json_object* price;

    parsed_json = json_tokener_parse(json_str);

    if (json_object_object_get_ex(parsed_json, "product_name", &product_name)) {
        product->product_name = strdup(json_object_get_string(product_name));
    }

    if (json_object_object_get_ex(parsed_json, "category", &category)) {
        product->category = strdup(json_object_get_string(category));
    }

    if (json_object_object_get_ex(parsed_json, "price", &price)) {
        product->price = json_object_get_double(price);
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"product_name\":\"Wireless Headphones\",\"category\":\"Electronics\",\"price\":149.99}";
    Product product;

    deserialize_product(json_str, &product);

    printf("Product Name: %s\n", product.product_name);
    printf("Category: %s\n", product.category);
    printf("Price: %.2f\n", product.price);

    free(product.product_name);
    free(product.category);

    return 0;
}