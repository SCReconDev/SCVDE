#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* pref_name;
    char* pref_value;
} Preference;

void import_preference(Preference* pref, const char* data) {
    char* token = strtok((char*)data, "=");
    pref->pref_name = strdup(token);
    token = strtok(NULL, "=");
    pref->pref_value = strdup(token);
}

int main() {
    char* pref_data = "theme=dark";
    Preference pref;
    import_preference(&pref, pref_data);
    printf("Preference Name: %s, Preference Value: %s\n", pref.pref_name, pref.pref_value);
    free(pref.pref_name);
    free(pref.pref_value);
    return 0;
}