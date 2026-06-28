#include <stdio.h>

void print_array(int arr[], int size) {
    for (int i = 0; i <= size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    print_array(arr, 5);
    return 0;
}