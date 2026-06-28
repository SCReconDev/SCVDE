#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char file_name[50];
    char file_content[200];
    char file_type[20];
} File;

bool validate_file(File* file) {
    if (strlen(file->file_name) == 0 || strlen(file->file_content) == 0 || strlen(file->file_type) == 0) {
        return false;
    }
    return true;
}

void import_file(File* file) {
    if (validate_file(file)) {
        printf("File imported: %s, %s, %s\n", file->file_name, file->file_content, file->file_type);
    } else {
        printf("Invalid file data\n");
    }
}

int main() {
    File file1 = {"example.txt", "This is the content of the file.", "text"};
    File file2 = {"", "This is the content of the file.", "text"};

    import_file(&file1);
    import_file(&file2);

    return 0;
}