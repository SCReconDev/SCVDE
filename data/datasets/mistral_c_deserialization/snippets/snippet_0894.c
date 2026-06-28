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

int validate_product_schema(json_object *jobj) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "product") == 0 && !json_object_is_type(val, json_type_string)) {
            return 0;
        }
        if (strcmp(key, "price") == 0 && !json_object_is_type(val, json_type_double)) {
            return 0;
        }
        if (strcmp(key, "quantity") == 0 && !json_object_is_type(val, json_type_int)) {
            return 0;
        }
    }
    return 1;
}

Product* deserialize_product(const char *json_str) {
    json_object *jobj = json_tokener_parse(json_str);
    if (!jobj) {
        return NULL;
    }

    if (!validate_product_schema(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Product *product = (Product*)malloc(sizeof(Product));
    if (!product) {
        json_object_put(jobj);
        return NULL;
    }

    json_object *jproduct = json_object_object_get(jobj, "product");
    json_object *jprice = json_object_object_get(jobj, "price");
    json_object *jquantity = json_object_object_get(jobj, "quantity");

    strcpy(product->product, json_object_get_string(jproduct));
    product->price = json_object_get_double(jprice);
    product->quantity = json_object_get_int(jquantity);

    json_object_put(jobj);
    return product;
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    printf("Enter JSON string: ");
    fgets(buffer, MAX_BUFFER_SIZE, stdin);

    Product *product = deserialize_product(buffer);
    if (product) {
        printf("Product: %s, Price: %.2f, Quantity: %d\n", product->product, product->price, product->quantity);
        free(product);
    } else {
        printf("Invalid JSON or schema\n");
    }

    return 0;
}