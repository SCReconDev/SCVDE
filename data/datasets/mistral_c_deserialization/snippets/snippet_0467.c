#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    float price;
} Product;

void deserialize_product(Product* product, const char* data) {
    char* token = strtok((char*)data, ";");
    product->name = strdup(token);
    token = strtok(NULL, ";");
    product->price = atof(token);
}

int main() {
    char* data = "Laptop;999.99";
    Product product;
    deserialize_product(&product, data);
    printf("Product: %s, Price: %.2f\n", product.name, product.price);
    free(product.name);
    return 0;
}