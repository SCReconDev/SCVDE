#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* filename;
    char* content;
} FileData;

void import_file(FileData* file, const char* data) {
    char* token = strtok((char*)data, "::");
    file->filename = strdup(token);
    token = strtok(NULL, "::");
    file->content = strdup(token);
}

int main() {
    char* file_data = "example.txt::This is the content of the file.";
    FileData file;
    import_file(&file, file_data);
    printf("Filename: %s, Content: %s\n", file.filename, file.content);
    free(file.filename);
    free(file.content);
    return 0;
}