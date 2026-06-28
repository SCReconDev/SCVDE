#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* filename;
    int size;
    char* content;
} File;

void import_file(const char* data, File* file) {
    char* token = strtok((char*)data, ",");
    file->filename = strdup(token);
    token = strtok(NULL, ",");
    file->size = atoi(token);
    token = strtok(NULL, ",");
    file->content = strdup(token);
}

int main() {
    char* file_data = "document.txt,1024,This is the content of the file.";
    File file;
    import_file(file_data, &file);
    printf("Filename: %s, Size: %d, Content: %s\n", file.filename, file.size, file.content);
    free(file.filename);
    free(file.content);
    return 0;
}