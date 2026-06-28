#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

typedef struct {
    char* product_id;
    float price;
} Product;

bool validate_product_schema(const cJSON* json) {
    if (!cJSON_IsObject(json)) return false;
    cJSON* product_id = cJSON_GetObjectItemCaseSensitive(json, "product_id");
    cJSON* price = cJSON_GetObjectItemCaseSensitive(json, "price");
    if (!cJSON_IsString(product_id) || !cJSON_IsNumber(price)) return false;
    return true;
}

Product* deserialize_product(const char* json_str) {
    cJSON* json = cJSON_Parse(json_str);
    if (!json || !validate_product_schema(json)) {
        cJSON_Delete(json);
        return NULL;
    }

    Product* product = malloc(sizeof(Product));
    if (!product) {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON* product_id = cJSON_GetObjectItemCaseSensitive(json, "product_id");
    cJSON* price = cJSON_GetObjectItemCaseSensitive(json, "price");

    product->product_id = strdup(product_id->valuestring);
    product->price = (float)price->valuedouble;

    cJSON_Delete(json);
    return product;
}

void free_product(Product* product) {
    if (product) {
        free(product->product_id);
        free(product);
    }
}

int main() {
    const char* json_str = "{\"product_id\":\"12345\",\"price\":19.99}";
    Product* product = deserialize_product(json_str);

    if (product) {
        printf("Product ID: %s\nPrice: %.2f\n", product->product_id, product->price);
        free_product(product);
    } else {
        printf("Failed to deserialize product.\n");
    }

    return 0;
}