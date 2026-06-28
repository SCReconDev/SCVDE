#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char preference_name[50];
    char preference_value[100];
} UserPreference;

void import_preferences(const char* user_file, UserPreference* pref) {
    char* data = strdup(user_file);
    char* token = strtok(data, "=");
    strcpy(pref->preference_name, token);
    token = strtok(NULL, "=");
    strcpy(pref->preference_value, token);
    free(data);
}

int main() {
    char* user_file = "theme=dark";
    UserPreference pref;
    import_preferences(user_file, &pref);
    printf("Preference Name: %s, Preference Value: %s\n", pref.preference_name, pref.preference_value);
    return 0;
}