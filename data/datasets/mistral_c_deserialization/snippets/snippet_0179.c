#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* data;
    int length;
} Data;

void restore_data(char* file) {
    Data* data = (Data*)malloc(sizeof(Data));
    memcpy(data, file, sizeof(Data));
    printf("Data Length: %d\n", data->length);
    free(data);
}

int main() {
    char file[1024];
    fgets(file, sizeof(file), stdin);
    restore_data(file);
    return 0;
}