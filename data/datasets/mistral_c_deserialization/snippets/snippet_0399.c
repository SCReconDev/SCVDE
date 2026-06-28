#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* filename;
    char* data;
} RestoreData;

void restore_data(RestoreData* data) {
    printf("Filename: %s\n", data->filename);
    printf("Data: %s\n", data->data);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    char* input_file = argv[1];
    RestoreData* data = (RestoreData*)input_file;
    restore_data(data);

    return 0;
}