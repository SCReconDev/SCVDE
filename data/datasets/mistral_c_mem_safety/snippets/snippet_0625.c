#include <stdio.h>

void print_value(int *ptr) {
    if (ptr == NULL) {
        printf("Invalid pointer\n");
        return;
    }
    printf("Value: %d\n", *ptr);
}

int main() {
    int value;
    printf("Enter value: ");
    scanf("%d", &value);
    int *ptr = &value;
    print_value(ptr);
    return 0;
}