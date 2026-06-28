#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *product_id;
    float price;
} Product;

void deserialize_product(const char *json_str, Product *product) {
    struct json_object *parsed_json;
    struct json_object *product_id_obj, *price_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "product_id", &product_id_obj) ||
        !json_object_object_get_ex(parsed_json, "price", &price_obj)) {
        fprintf(stderr, "Error: Missing required fields\n");
        json_object_put(parsed_json);
        return;
    }

    if (json_object_get_type(product_id_obj) != json_type_string ||
        json_object_get_type(price_obj) != json_type_double) {
        fprintf(stderr, "Error: Invalid field types\n");
        json_object_put(parsed_json);
        return;
    }

    product->product_id = strdup(json_object_get_string(product_id_obj));
    product->price = (float)json_object_get_double(price_obj);

    json_object_put(parsed_json);
}

void process_product(Product *product) {
    printf("Product ID: %s\n", product->product_id);
    printf("Price: %.2f\n", product->price);
}

int main() {
    const char *json_str = "{\"product_id\": \"12345\", \"price\": 19.99}";
    Product product;

    deserialize_product(json_str, &product);
    process_product(&product);

    free(product.product_id);
    return 0;
}