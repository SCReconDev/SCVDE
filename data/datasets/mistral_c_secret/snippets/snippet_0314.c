#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "sk_test_4eC39HqLyjWDarjtT1zdp7dc"

void process_payment(int amount) {
    printf("Processing payment of $%d with secret key: %s\n", amount, SECRET_KEY);
}

int main() {
    process_payment(100);
    return 0;
}