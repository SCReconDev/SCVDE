#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char filename[50];
    char content[100];
} FileState;

void import_file(const char* state) {
    FileState* file = (FileState*)malloc(sizeof(FileState));
    memcpy(file, state, sizeof(FileState));
    printf("Filename: %s, Content: %s\n", file->filename, file->content);
    free(file);
}

int main() {
    char state[sizeof(FileState)];
    memset(state, 0, sizeof(state));
    strcpy(state, "example.txt");
    strcpy(state + 50, "This is an example content.");

    import_file(state);
    return 0;
}