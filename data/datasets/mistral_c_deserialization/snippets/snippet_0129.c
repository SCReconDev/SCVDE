#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 1024

void restore_data(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("fopen");
        return;
    }

    char *input_data = (char *)malloc(INPUT_SIZE);
    if (input_data == NULL) {
        fclose(file);
        return;
    }

    size_t bytes_read = fread(input_data, 1, INPUT_SIZE - 1, file);
    if (bytes_read == 0) {
        free(input_data);
        fclose(file);
        return;
    }
    input_data[bytes_read] = '\0';

    void *data = deserialize_data(input_data, bytes_read);
    if (data == NULL) {
        free(input_data);
        fclose(file);
        return;
    }

    printf("Data restored successfully.\n");

    free(data);
    free(input_data);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    restore_data(argv[1]);

    return 0;
}