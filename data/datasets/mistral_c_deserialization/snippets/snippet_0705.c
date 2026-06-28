#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char file_name[50];
    char file_content[255];
} FileData;

bool validate_file_data(FileData* file_data) {
    if (strlen(file_data->file_name) == 0 || strlen(file_data->file_name) >= 50) {
        return false;
    }
    if (strlen(file_data->file_content) >= 255) {
        return false;
    }
    return true;
}

void process_file_data(FileData* file_data) {
    if (validate_file_data(file_data)) {
        printf("File Name: %s, Content: %s\n", file_data->file_name, file_data->file_content);
    } else {
        printf("Invalid file data\n");
    }
}

int main() {
    FileData file1 = {"example.txt", "This is the content of the file."};
    FileData file2 = {"", "Invalid content"};

    process_file_data(&file1);
    process_file_data(&file2);

    return 0;
}