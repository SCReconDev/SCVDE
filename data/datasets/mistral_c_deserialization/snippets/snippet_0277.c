#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* data;
} FileData;

void import_file(FileData* file, const char* state) {
    char* token = strtok((char*)state, ",");
    file->name = strdup(token);
    token = strtok(NULL, ",");
    file->data = strdup(token);
}

int main() {
    char state[100];
    printf("Enter file state: ");
    fgets(state, sizeof(state), stdin);
    state[strcspn(state, "\n")] = 0;

    FileData file;
    import_file(&file, state);

    printf("Name: %s, Data: %s\n", file.name, file.data);
    free(file.name);
    free(file.data);
    return 0;
}