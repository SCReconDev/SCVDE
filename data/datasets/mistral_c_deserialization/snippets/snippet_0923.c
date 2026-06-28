#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *product_name;
    float price;
    int quantity;
} Product;

void update_inventory(Product *product) {
    printf("Product: %s, Price: %.2f, Quantity: %d\n", product->product_name, product->price, product->quantity);
}

int main() {
    const char *json_str = "{\"product_name\":\"Laptop\", \"price\":999.99, \"quantity\":5}";
    struct json_object *parsed_json;
    struct json_object *product_name_obj, *price_obj, *quantity_obj;
    Product product;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    if (!json_object_object_get_ex(parsed_json, "product_name", &product_name_obj) ||
        !json_object_object_get_ex(parsed_json, "price", &price_obj) ||
        !json_object_object_get_ex(parsed_json, "quantity", &quantity_obj)) {
        fprintf(stderr, "Error extracting JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    product.product_name = strdup(json_object_get_string(product_name_obj));
    product.price = json_object_get_double(price_obj);
    product.quantity = json_object_get_int(quantity_obj);

    update_inventory(&product);

    free(product.product_name);
    json_object_put(parsed_json);

    return 0;
}