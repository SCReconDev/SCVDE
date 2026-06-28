#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char restore_id[50];
    char restore_data[200];
} RestoreData;

void deserialize_restore_data(RestoreData *restore_data, const char *data) {
    memcpy(restore_data, data, sizeof(RestoreData));
}

void restore_data(const char *input_file) {
    RestoreData restore_data;
    deserialize_restore_data(&restore_data, input_file);
    printf("Restored data: %s\n", restore_data.restore_id);
}

int main() {
    char input_file[250];
    printf("Enter input file: ");
    fgets(input_file, sizeof(input_file), stdin);
    input_file[strcspn(input_file, "\n")] = '\0';

    restore_data(input_file);
    return 0;
}