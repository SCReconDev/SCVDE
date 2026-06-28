#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char filename[50];
    char content[100];
} File;

void import_file(const char* state) {
    File* file = (File*)malloc(sizeof(File));
    memcpy(file, state, sizeof(File));
    printf("File: %s, Content: %s\n", file->filename, file->content);
    free(file);
}

int main() {
    char state[200];
    printf("Enter state: ");
    fgets(state, sizeof(state), stdin);
    import_file(state);
    return 0;
}