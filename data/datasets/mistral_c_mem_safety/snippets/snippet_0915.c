#include <stdio.h>
#include <stdlib.h>

void print_value(int *value) {
    if (value == NULL) {
        fprintf(stderr, "Invalid value\n");
        return;
    }

    printf("Value: %d\n", *value);
}

int main() {
    int *value = NULL;
    int input;

    printf("Enter value (0 to skip): ");
    scanf("%d", &input);

    if (input != 0) {
        value = (int *)malloc(sizeof(int));
        if (value == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        *value = input;
    }

    print_value(value);

    if (value != NULL) {
        free(value);
    }

    return 0;
}