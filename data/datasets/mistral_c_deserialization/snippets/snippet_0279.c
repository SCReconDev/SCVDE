#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* data;
} FileData;

void restore_data(FileData* file, const char* input) {
    char* token = strtok((char*)input, ",");
    file->name = strdup(token);
    token = strtok(NULL, ",");
    file->data = strdup(token);
}

int main() {
    char input[100];
    printf("Enter input file: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    FileData file;
    restore_data(&file, input);

    printf("Name: %s, Data: %s\n", file.name, file.data);
    free(file.name);
    free(file.data);
    return 0;
}