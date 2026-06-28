#include <stdio.h>
#include <stdlib.h>

void create_object() {
    int *ptr = (int *)malloc(sizeof(int));
    *ptr = 42;
}

int main() {
    create_object();
    return 0;
}