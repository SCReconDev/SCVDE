#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char filename[50];
    char content[200];
} FileData;

void deserialize_file_data(FileData *file, const char *state) {
    sscanf(state, "%49s %199[^\n]", file->filename, file->content);
}

void import_file(const char *state) {
    FileData file;
    deserialize_file_data(&file, state);
    printf("Filename: %s, Content: %s\n", file.filename, file.content);
}

int main() {
    char state[250];
    printf("Enter file state: ");
    fgets(state, sizeof(state), stdin);
    import_file(state);
    return 0;
}