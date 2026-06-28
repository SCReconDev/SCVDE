#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* filename;
    char* content;
} FileData;

void deserialize_file(const char* state, FileData* file) {
    char* token = strtok((char*)state, ":");
    file->filename = strdup(token);
    token = strtok(NULL, ":");
    file->content = strdup(token);
}

int main() {
    char* state = "example.txt:This is the content of the file.";
    FileData file;
    deserialize_file(state, &file);
    printf("Filename: %s, Content: %s\n", file.filename, file.content);
    free(file.filename);
    free(file.content);
    return 0;
}