#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[256];
    char value[256];
} Preference;

void deserialize_preference(Preference *preference, const char *data) {
    sscanf(data, "%255[^;];%255[^;]", preference->key, preference->value);
}

void import_preferences(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    char buffer[512];
    fgets(buffer, sizeof(buffer), file);
    fclose(file);
    Preference preference;
    deserialize_preference(&preference, buffer);
    printf("Preference: %s = %s\n", preference.key, preference.value);
}

int main() {
    char file_path[256];
    printf("Enter file path: ");
    fgets(file_path, sizeof(file_path), stdin);
    file_path[strcspn(file_path, "\n")] = 0;
    import_preferences(file_path);
    return 0;
}