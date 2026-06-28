#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* filename;
    char* content;
} FileData;

void import_file(FileData* file) {
    printf("Filename: %s\n", file->filename);
    printf("Content: %s\n", file->content);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <uploaded_state_file>\n", argv[0]);
        return 1;
    }

    char* uploaded_state_file = argv[1];
    FileData* file = (FileData*)uploaded_state_file;
    import_file(file);

    return 0;
}