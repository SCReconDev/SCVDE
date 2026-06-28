#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int size;
} File;

void import_file(char* state) {
    File* file = (File*)malloc(sizeof(File));
    memcpy(file, state, sizeof(File));
    printf("File: %s, Size: %d\n", file->name, file->size);
    free(file);
}

int main() {
    char state[1024];
    fgets(state, sizeof(state), stdin);
    import_file(state);
    return 0;
}