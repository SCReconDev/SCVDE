#include <stdio.h>

void iterate_array() {
    int array[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    iterate_array();
    return 0;
}