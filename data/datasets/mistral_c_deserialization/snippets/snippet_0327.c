#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char filename[50];
    char content[100];
} FileData;

void deserialize_file_data(const char* data, FileData* file) {
    sscanf(data, "%49[^|]|%99[^|]", file->filename, file->content);
}

int main() {
    char state_file[200];
    FileData file;

    printf("Enter state file data (filename|content): ");
    fgets(state_file, sizeof(state_file), stdin);
    state_file[strcspn(state_file, "\n")] = '\0';

    deserialize_file_data(state_file, &file);

    printf("Filename: %s\nContent: %s\n", file.filename, file.content);

    return 0;
}