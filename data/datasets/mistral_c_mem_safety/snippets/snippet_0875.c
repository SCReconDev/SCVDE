#include <stdio.h>
#include <stdlib.h>

void print_value(int *ptr) {
    if (ptr == NULL) {
        printf("Null pointer\n");
        return;
    }
    printf("Value: %d\n", *ptr);
}

int main() {
    int *ptr = NULL;
    int value = 42;
    int choice;
    printf("Enter choice (1 for null, 2 for value): ");
    scanf("%d", &choice);
    if (choice == 2) {
        ptr = &value;
    }
    print_value(ptr);
    return 0;
}