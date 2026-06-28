#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PREFERENCES_SIZE 1024

void import_preferences(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("fopen");
        return;
    }

    char *preferences_data = (char *)malloc(PREFERENCES_SIZE);
    if (preferences_data == NULL) {
        fclose(file);
        return;
    }

    size_t bytes_read = fread(preferences_data, 1, PREFERENCES_SIZE - 1, file);
    if (bytes_read == 0) {
        free(preferences_data);
        fclose(file);
        return;
    }
    preferences_data[bytes_read] = '\0';

    void *preferences = deserialize_preferences(preferences_data, bytes_read);
    if (preferences == NULL) {
        free(preferences_data);
        fclose(file);
        return;
    }

    printf("Preferences imported successfully.\n");

    free(preferences);
    free(preferences_data);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <preferences_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    import_preferences(argv[1]);

    return 0;
}