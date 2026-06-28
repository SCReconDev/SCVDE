#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* product_name;
    float price;
    int quantity;
} Product;

void print_product(Product* product) {
    printf("Product Name: %s\n", product->product_name);
    printf("Price: %.2f\n", product->price);
    printf("Quantity: %d\n", product->quantity);
}

int main() {
    const char* json_str = "{\"product_name\":\"Laptop\",\"price\":999.99,\"quantity\":5}";
    struct json_object* parsed_json;
    struct json_object* product_name;
    struct json_object* price;
    struct json_object* quantity;
    Product product;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    json_object_object_get_ex(parsed_json, "product_name", &product_name);
    json_object_object_get_ex(parsed_json, "price", &price);
    json_object_object_get_ex(parsed_json, "quantity", &quantity);

    if (product_name == NULL || price == NULL || quantity == NULL) {
        fprintf(stderr, "Invalid JSON structure\n");
        json_object_put(parsed_json);
        return 1;
    }

    product.product_name = strdup(json_object_get_string(product_name));
    product.price = json_object_get_double(price);
    product.quantity = json_object_get_int(quantity);

    print_product(&product);

    free(product.product_name);
    json_object_put(parsed_json);

    return 0;
}