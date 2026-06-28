#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char preference_name[50];
    char value[100];
} Preference;

void load_preference(const char* data, Preference* pref) {
    sscanf(data, "%49s %99[^\n]", pref->preference_name, pref->value);
}

int main() {
    char user_file[200];
    Preference pref;

    printf("Enter user file data (preference_name value): ");
    fgets(user_file, sizeof(user_file), stdin);

    load_preference(user_file, &pref);

    printf("Loaded Preference: Preference Name=%s, Value=%s\n", pref.preference_name, pref.value);

    return 0;
}