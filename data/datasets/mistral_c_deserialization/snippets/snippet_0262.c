#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* pref_name;
    int pref_value;
} Preference;

void deserialize_preference(char* data, Preference* pref) {
    char* token = strtok(data, "=");
    pref->pref_name = strdup(token);
    token = strtok(NULL, "=");
    pref->pref_value = atoi(token);
}

void import_preferences(char* user_file) {
    Preference pref;
    deserialize_preference(user_file, &pref);
    printf("Preference: %s, Value: %d\n", pref.pref_name, pref.pref_value);
    free(pref.pref_name);
}

int main() {
    char* user_file = "timeout=30";
    import_preferences(user_file);
    return 0;
}