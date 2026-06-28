#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char filename[50];
    char content[100];
} File;

void deserialize_file(const char* data, File* file) {
    char* decoded_data = malloc(strlen(data) + 1);
    strcpy(decoded_data, data);
    sscanf(decoded_data, "%49s %99[^\n]", file->filename, file->content);
    free(decoded_data);
}

void import_file(const char* file_data) {
    File file;
    deserialize_file(file_data, &file);
    printf("Imported file: %s with content: %s\n", file.filename, file.content);
}

int main() {
    const char* file_data = "document.txt This is a test document.";
    import_file(file_data);
    return 0;
}