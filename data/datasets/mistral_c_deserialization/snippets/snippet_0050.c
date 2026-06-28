#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* theme;
    int font_size;
} Preferences;

void process_preferences(Preferences* prefs) {
    printf("Theme: %s\n", prefs->theme);
    printf("Font Size: %d\n", prefs->font_size);
}

void deserialize_preferences(const char* file_content, Preferences* prefs) {
    char* data = strdup(file_content);
    char* token = strtok(data, "|");
    prefs->theme = strdup(token);
    token = strtok(NULL, "|");
    prefs->font_size = atoi(token);
    free(data);
}

void import_preferences(const char* file_content) {
    Preferences prefs;
    deserialize_preferences(file_content, &prefs);
    process_preferences(&prefs);
}

int main() {
    const char* file_content = "dark|12";
    import_preferences(file_content);
    return 0;
}