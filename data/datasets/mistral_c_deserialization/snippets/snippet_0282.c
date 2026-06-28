#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* data;
} Preferences;

void import_preferences(Preferences* prefs, const char* user_file) {
    char* token = strtok((char*)user_file, ",");
    prefs->name = strdup(token);
    token = strtok(NULL, ",");
    prefs->data = strdup(token);
}

int main() {
    char user_file[100];
    printf("Enter user file: ");
    fgets(user_file, sizeof(user_file), stdin);
    user_file[strcspn(user_file, "\n")] = 0;

    Preferences prefs;
    import_preferences(&prefs, user_file);

    printf("Name: %s, Data: %s\n", prefs.name, prefs.data);
    free(prefs.name);
    free(prefs.data);
    return 0;
}