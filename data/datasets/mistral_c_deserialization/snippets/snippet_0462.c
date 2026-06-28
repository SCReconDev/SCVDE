#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char preference_key[50];
    char preference_value[100];
} Preference;

void deserialize_preference(char* data, Preference* pref) {
    char* token = strtok(data, ":");
    strcpy(pref->preference_key, token);
    token = strtok(NULL, ":");
    strcpy(pref->preference_value, token);
}

void import_preferences(char* user_file) {
    Preference pref;
    deserialize_preference(user_file, &pref);
    printf("Imported preference: %s = %s\n", pref.preference_key, pref.preference_value);
}

int main() {
    char user_file[] = "theme:dark";
    import_preferences(user_file);
    return 0;
}