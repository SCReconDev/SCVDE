#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char file_name[50];
    char file_data[200];
} FileData;

void deserialize_file_data(FileData *file_data, const char *data) {
    memcpy(file_data, data, sizeof(FileData));
}

void import_file(const char *state_file) {
    FileData file_data;
    deserialize_file_data(&file_data, state_file);
    printf("Imported file: %s\n", file_data.file_name);
}

int main() {
    char state_file[250];
    printf("Enter state file: ");
    fgets(state_file, sizeof(state_file), stdin);
    state_file[strcspn(state_file, "\n")] = '\0';

    import_file(state_file);
    return 0;
}