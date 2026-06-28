#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* preference_name;
    int preference_value;
} Preference;

void load_preference(Preference* pref, const char* data) {
    char* token = strtok((char*)data, "=");
    pref->preference_name = strdup(token);
    token = strtok(NULL, "=");
    pref->preference_value = atoi(token);
}

int main() {
    const char* data = "theme=dark";
    Preference pref;
    load_preference(&pref, data);
    printf("Preference Name: %s, Preference Value: %d\n", pref.preference_name, pref.preference_value);
    free(pref.preference_name);
    return 0;
}