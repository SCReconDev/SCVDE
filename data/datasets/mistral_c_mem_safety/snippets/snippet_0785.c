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
    int choice;
    printf("Enter 1 to allocate memory, 0 to keep null: ");
    scanf("%d", &choice);
    if (choice == 1) {
        ptr = (int *)malloc(sizeof(int));
        if (ptr == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        *ptr = 42;
    }
    print_value(ptr);
    if (ptr != NULL) {
        free(ptr);
    }
    return 0;
}