#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char filename[50];
    char data[100];
} RestoreData;

void restore_data(const char* input) {
    RestoreData* data = (RestoreData*)malloc(sizeof(RestoreData));
    memcpy(data, input, sizeof(RestoreData));
    printf("Filename: %s, Data: %s\n", data->filename, data->data);
    free(data);
}

int main() {
    char input[sizeof(RestoreData)];
    memset(input, 0, sizeof(input));
    strcpy(input, "backup.dat");
    strcpy(input + 50, "Backup data content.");

    restore_data(input);
    return 0;
}