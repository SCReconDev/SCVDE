#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    char value[50];
} Preference;

void load_preference(Preference *pref, const char *data) {
    sscanf(data, "%49s %49s", pref->key, pref->value);
}

void import_preferences(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        char data[100];
        fgets(data, sizeof(data), file);
        Preference pref;
        load_preference(&pref, data);
        printf("Preference: %s = %s\n", pref.key, pref.value);
        fclose(file);
    }
}

int main() {
    char filename[50];
    printf("Enter preferences file: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;
    import_preferences(filename);
    return 0;
}