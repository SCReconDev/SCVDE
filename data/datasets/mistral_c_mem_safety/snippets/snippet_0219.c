#include <stdio.h>
#include <stdlib.h>

void create_object() {
    int *obj = (int *)malloc(sizeof(int));
    *obj = 100;
}

int main() {
    create_object();
    return 0;
}