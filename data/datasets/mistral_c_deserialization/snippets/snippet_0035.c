#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* filename;
    char* content;
} FileData;

void import_file(FileData* file, const char* state) {
    char* token = strtok((char*)state, "|");
    file->filename = strdup(token);
    token = strtok(NULL, "|");
    file->content = strdup(token);
}

int main() {
    char* state = "file.txt|This is the file content.";
    FileData file;
    import_file(&file, state);
    printf("Filename: %s, Content: %s\n", file.filename, file.content);
    free(file.filename);
    free(file.content);
    return 0;
}