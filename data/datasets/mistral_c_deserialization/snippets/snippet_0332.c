#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char preference_name[50];
    char preference_value[100];
} Preference;

void deserialize_preference(const char* data, Preference* pref) {
    sscanf(data, "%49[^|]|%99[^|]", pref->preference_name, pref->preference_value);
}

int main() {
    char user_file[200];
    Preference pref;

    printf("Enter user file data (preference_name|preference_value): ");
    fgets(user_file, sizeof(user_file), stdin);
    user_file[strcspn(user_file, "\n")] = '\0';

    deserialize_preference(user_file, &pref);

    printf("Preference Name: %s\nPreference Value: %s\n", pref.preference_name, pref.preference_value);

    return 0;
}