#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char product[50];
    float price;
    int quantity;
} Product;

void show_product(Product *product) {
    printf("Product: %s\n", product->product);
    printf("Price: %.2f\n", product->price);
    printf("Quantity: %d\n", product->quantity);
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    FILE *file = fopen("product.json", "r");
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

    struct json_object *product_obj, *price_obj, *quantity_obj;
    if (!json_object_object_get_ex(parsed_json, "product", &product_obj) ||
        !json_object_object_get_ex(parsed_json, "price", &price_obj) ||
        !json_object_object_get_ex(parsed_json, "quantity", &quantity_obj)) {
        fprintf(stderr, "Error accessing JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    Product product;
    strncpy(product.product, json_object_get_string(product_obj), sizeof(product.product) - 1);
    product.price = json_object_get_double(price_obj);
    product.quantity = json_object_get_int(quantity_obj);

    show_product(&product);

    json_object_put(parsed_json);
    return 0;
}