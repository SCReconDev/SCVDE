#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* setting_name;
    char* setting_value;
} UserPreference;

void import_preferences(const char* file) {
    UserPreference pref;
    char* decoded = strdup(file);
    char* token = strtok(decoded, "=");
    pref.setting_name = strdup(token);
    token = strtok(NULL, "=");
    pref.setting_value = strdup(token);
    printf("Preference imported: %s = %s\n", pref.setting_name, pref.setting_value);
    free(pref.setting_name);
    free(pref.setting_value);
    free(decoded);
}

int main() {
    const char* file = "language=en";
    import_preferences(file);
    return 0;
}