#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* preference_name;
    char* value;
} Preference;

void import_preference(Preference* pref, const char* data) {
    char* token = strtok((char*)data, ":");
    pref->preference_name = strdup(token);
    token = strtok(NULL, ":");
    pref->value = strdup(token);
}

int main() {
    char* data = "theme:dark";
    Preference pref;
    import_preference(&pref, data);
    printf("Preference Name: %s, Value: %s\n", pref.preference_name, pref.value);
    free(pref.preference_name);
    free(pref.value);
    return 0;
}