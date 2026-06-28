#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* preference_name;
    char* preference_value;
} UserPreference;

void deserialize_preference(const char* file_content, UserPreference* preference) {
    char* token = strtok((char*)file_content, "=");
    preference->preference_name = strdup(token);
    token = strtok(NULL, "=");
    preference->preference_value = strdup(token);
}

void import_preferences(const char* file_content) {
    UserPreference preference;
    deserialize_preference(file_content, &preference);
    printf("Preference Name: %s, Preference Value: %s\n", preference.preference_name, preference.preference_value);
    free(preference.preference_name);
    free(preference.preference_value);
}

int main() {
    const char* file_content = "theme=dark";
    import_preferences(file_content);
    return 0;
}