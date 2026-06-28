#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* preference_name;
    char* preference_value;
} Preference;

void deserialize_preference(const char* file_content, Preference* pref) {
    char* token = strtok((char*)file_content, "=");
    pref->preference_name = strdup(token);

    token = strtok(NULL, "=");
    pref->preference_value = strdup(token);
}

int main() {
    const char* file_content = "theme=dark";
    Preference pref;

    deserialize_preference(file_content, &pref);

    printf("Preference Name: %s, Preference Value: %s\n", pref.preference_name, pref.preference_value);

    free(pref.preference_name);
    free(pref.preference_value);
    return 0;
}