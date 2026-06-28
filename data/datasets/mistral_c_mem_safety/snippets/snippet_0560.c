#include <stdio.h>
#include <stdlib.h>

void validate_length(size_t length) {
    if (length > 0 && length <= 100) {
        printf("Valid length: %zu\n", length);
    } else {
        printf("Invalid length.\n");
    }
}

int main() {
    size_t length;
    printf("Enter length: ");
    scanf("%zu", &length);
    validate_length(length);
    return 0;
}