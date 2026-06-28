#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char* name;
    float price;
} Product;

void restore_cache(const char* data, Product* product) {
    char* token = strtok((char*)data, "|");
    product->id = atoi(token);
    token = strtok(NULL, "|");
    product->name = strdup(token);
    token = strtok(NULL, "|");
    product->price = atof(token);
}

int main() {
    char* cache_data = "123|Laptop|999.99";
    Product product;
    restore_cache(cache_data, &product);
    printf("ID: %d, Name: %s, Price: %.2f\n", product.id, product.name, product.price);
    free(product.name);
    return 0;
}