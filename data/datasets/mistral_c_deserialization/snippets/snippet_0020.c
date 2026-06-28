#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* preference_name;
    int setting;
} UserPreference;

void deserialize_user_preference(UserPreference* preference, const char* data) {
    char* token = strtok((char*)data, ",");
    preference->preference_name = strdup(token);
    token = strtok(NULL, ",");
    preference->setting = atoi(token);
}

void import_preferences(const char* user_file_data) {
    UserPreference preference;
    deserialize_user_preference(&preference, user_file_data);
    printf("User Preference - Name: %s, Setting: %d\n", preference.preference_name, preference.setting);
    free(preference.preference_name);
}

int main() {
    const char* user_file_data = "dark_mode,1";
    import_preferences(user_file_data);
    return 0;
}