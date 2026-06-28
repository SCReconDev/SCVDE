#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char pref_name[50];
    char pref_value[100];
} Preference;

void deserialize_preference(Preference *pref, const char *data) {
    char *token = strtok((char *)data, "=");
    strcpy(pref->pref_name, token);
    token = strtok(NULL, "=");
    strcpy(pref->pref_value, token);
}

void import_preferences(const char *file) {
    Preference pref;
    deserialize_preference(&pref, file);
    printf("Preferences imported: Name=%s, Value=%s\n", pref.pref_name, pref.pref_value);
}

int main() {
    const char *file = "theme=dark";
    import_preferences(file);
    return 0;
}