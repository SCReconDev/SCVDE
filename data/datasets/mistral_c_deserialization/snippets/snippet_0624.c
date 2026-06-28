#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *product_name;
    float price;
    int quantity;
} Product;

void deserialize_product(const char *json_str, Product *product) {
    struct json_object *parsed_json;
    struct json_object *product_name;
    struct json_object *price;
    struct json_object *quantity;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "product_name", &product_name);
    json_object_object_get_ex(parsed_json, "price", &price);
    json_object_object_get_ex(parsed_json, "quantity", &quantity);

    if (product_name != NULL && json_object_is_type(product_name, json_type_string)) {
        product->product_name = strdup(json_object_get_string(product_name));
    } else {
        product->product_name = NULL;
    }

    if (price != NULL && json_object_is_type(price, json_type_double)) {
        product->price = json_object_get_double(price);
    } else {
        product->price = 0.0f;
    }

    if (quantity != NULL && json_object_is_type(quantity, json_type_int)) {
        product->quantity = json_object_get_int(quantity);
    } else {
        product->quantity = 0;
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"product_name\":\"Laptop\",\"price\":999.99,\"quantity\":10}";
    Product product;

    deserialize_product(json_str, &product);

    printf("Product Name: %s\n", product.product_name);
    printf("Price: %.2f\n", product.price);
    printf("Quantity: %d\n", product.quantity);

    free(product.product_name);
    return 0;
}