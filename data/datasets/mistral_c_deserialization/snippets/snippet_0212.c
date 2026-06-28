#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char preference_name[50];
    char preference_value[100];
} UserPreference;

void deserialize_preference(UserPreference *pref, const char *data) {
    sscanf(data, "%49s %99[^\n]", pref->preference_name, pref->preference_value);
}

void import_preferences(const char *data) {
    UserPreference pref;
    deserialize_preference(&pref, data);
    printf("User Preference: %s = %s\n", pref.preference_name, pref.preference_value);
}

int main() {
    char data[200];
    printf("Enter user preference data: ");
    fgets(data, sizeof(data), stdin);
    import_preferences(data);
    return 0;
}