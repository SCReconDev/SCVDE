#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
} Data;

void use_data(Data *data) {
    if (data == NULL) {
        printf("Null data\n");
        return;
    }
    printf("Data value: %d\n", data->value);
}

int main() {
    Data *data = (Data *)malloc(sizeof(Data));
    if (data == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    data->value = 42;
    use_data(data);
    free(data);
    use_data(data);
    return 0;
}