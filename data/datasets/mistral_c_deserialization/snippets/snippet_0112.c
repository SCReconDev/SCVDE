#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* pref_name;
    char* pref_value;
} Preference;

void import_preference(Preference* pref, const char* file_content) {
    char* token = strdup(file_content);
    char* part = strtok(token, "|");
    pref->pref_name = strdup(part);
    part = strtok(NULL, "|");
    pref->pref_value = strdup(part);
    free(token);
}

int main() {
    char* file_content = "theme|dark";
    Preference pref;
    import_preference(&pref, file_content);
    printf("Preference Name: %s, Value: %s\n", pref.pref_name, pref.pref_value);
    return 0;
}