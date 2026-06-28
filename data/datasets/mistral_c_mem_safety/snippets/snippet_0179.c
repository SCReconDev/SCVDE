#include <stdio.h>
#include <stdlib.h>

void create_object() {
    int *obj = (int *)malloc(sizeof(int));
    if (obj != NULL) {
        *obj = 42;
    }
}

int main() {
    create_object();
    return 0;
}