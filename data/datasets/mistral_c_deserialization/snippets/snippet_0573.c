#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>

typedef struct {
    char *product_id;
    char *product_name;
    double price;
} Product;

bool validate_product_schema(const json_object *jobj) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "product_id") == 0 && json_object_get_type(val) != json_type_string) {
            return false;
        }
        if (strcmp(key, "product_name") == 0 && json_object_get_type(val) != json_type_string) {
            return false;
        }
        if (strcmp(key, "price") == 0 && json_object_get_type(val) != json_type_double) {
            return false;
        }
    }
    return true;
}

Product *deserialize_product(const char *json_str) {
    json_object *jobj = json_tokener_parse(json_str);
    if (!jobj) {
        return NULL;
    }

    if (!validate_product_schema(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Product *product = malloc(sizeof(Product));
    if (!product) {
        json_object_put(jobj);
        return NULL;
    }

    json_object *product_id_obj, *product_name_obj, *price_obj;
    if (json_object_object_get_ex(jobj, "product_id", &product_id_obj)) {
        product->product_id = strdup(json_object_get_string(product_id_obj));
    } else {
        product->product_id = NULL;
    }

    if (json_object_object_get_ex(jobj, "product_name", &product_name_obj)) {
        product->product_name = strdup(json_object_get_string(product_name_obj));
    } else {
        product->product_name = NULL;
    }

    if (json_object_object_get_ex(jobj, "price", &price_obj)) {
        product->price = json_object_get_double(price_obj);
    } else {
        product->price = 0.0;
    }

    json_object_put(jobj);
    return product;
}

void free_product(Product *product) {
    if (product) {
        free(product->product_id);
        free(product->product_name);
        free(product);
    }
}

int main() {
    const char *json_str = "{\"product_id\":\"12345\",\"product_name\":\"Laptop\",\"price\":999.99}";
    Product *product = deserialize_product(json_str);

    if (product) {
        printf("Product ID: %s\n", product->product_id);
        printf("Product Name: %s\n", product->product_name);
        printf("Price: %.2f\n", product->price);
        free_product(product);
    } else {
        printf("Failed to deserialize product.\n");
    }

    return 0;
}