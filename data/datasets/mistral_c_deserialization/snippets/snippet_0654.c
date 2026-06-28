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
    struct json_object *name_obj, *price_obj, *quantity_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "product_name", &name_obj);
    json_object_object_get_ex(parsed_json, "price", &price_obj);
    json_object_object_get_ex(parsed_json, "quantity", &quantity_obj);

    if (name_obj != NULL && json_object_get_type(name_obj) == json_type_string) {
        product->product_name = strdup(json_object_get_string(name_obj));
    }

    if (price_obj != NULL && json_object_get_type(price_obj) == json_type_double) {
        product->price = json_object_get_double(price_obj);
    }

    if (quantity_obj != NULL && json_object_get_type(quantity_obj) == json_type_int) {
        product->quantity = json_object_get_int(quantity_obj);
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