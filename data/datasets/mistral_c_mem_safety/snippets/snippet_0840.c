#include <stdio.h>

void parse_data(int length) {
    if (length <= 0 || length > 100) {
        printf("Invalid length\n");
        return;
    }
    printf("Parsing data of length: %d\n", length);
}

int main() {
    parse_data(50);
    return 0;
}