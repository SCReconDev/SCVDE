#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    char data[100];
} FileData;

void deserialize_file_data(FileData *file, const char *data) {
    char *token = strtok((char *)data, ",");
    strcpy(file->name, token);
    token = strtok(NULL, ",");
    strcpy(file->data, token);
}

void import_file(const char *state) {
    FileData file;
    deserialize_file_data(&file, state);
    printf("File imported: Name=%s, Data=%s\n", file.name, file.data);
}

int main() {
    const char *state = "example.txt,This is an example.";
    import_file(state);
    return 0;
}