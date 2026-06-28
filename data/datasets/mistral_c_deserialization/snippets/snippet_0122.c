#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} Preference;

void import_preferences(const char* file_data, Preference* pref) {
    char* data = strdup(file_data);
    char* token = strtok(data, "=");
    pref->key = strdup(token);
    token = strtok(NULL, "=");
    pref->value = strdup(token);
    free(data);
}

int main() {
    char* file_data = "theme=dark";
    Preference pref;
    import_preferences(file_data, &pref);
    printf("Preference Key: %s, Preference Value: %s\n", pref.key, pref.value);
    free(pref.key);
    free(pref.value);
    return 0;
}