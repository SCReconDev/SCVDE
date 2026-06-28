#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char pref_name[50];
    char pref_data[200];
} Preferences;

void deserialize_preferences(Preferences *preferences, const char *data) {
    memcpy(preferences, data, sizeof(Preferences));
}

void import_preferences(const char *user_file) {
    Preferences preferences;
    deserialize_preferences(&preferences, user_file);
    printf("Imported preferences: %s\n", preferences.pref_name);
}

int main() {
    char user_file[250];
    printf("Enter user file: ");
    fgets(user_file, sizeof(user_file), stdin);
    user_file[strcspn(user_file, "\n")] = '\0';

    import_preferences(user_file);
    return 0;
}