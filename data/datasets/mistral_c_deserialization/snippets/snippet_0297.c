#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int size;
} File;

void import_file(const char* state) {
    File* file = (File*)malloc(sizeof(File));
    memcpy(file, state, sizeof(File));

    printf("File: %s, Size: %d\n", file->name, file->size);
    free(file);
}

int main() {
    char* file_state = "document.txt\01024";
    import_file(file_state);
    return 0;
}