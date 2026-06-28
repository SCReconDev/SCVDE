#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char preference_name[50];
    char preference_value[50];
} Preference;

void deserialize_preference(const char* data, Preference* pref) {
    char* decoded_data = malloc(strlen(data) + 1);
    strcpy(decoded_data, data);
    sscanf(decoded_data, "%49s %49s", pref->preference_name, pref->preference_value);
    free(decoded_data);
}

void import_preferences(const char* pref_data) {
    Preference pref;
    deserialize_preference(pref_data, &pref);
    printf("Preference: %s = %s\n", pref.preference_name, pref.preference_value);
}

int main() {
    const char* pref_data = "theme dark";
    import_preferences(pref_data);
    return 0;
}