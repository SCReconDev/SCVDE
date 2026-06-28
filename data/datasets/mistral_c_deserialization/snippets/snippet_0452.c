#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char pref_name[50];
    char pref_value[100];
} Preference;

void import_preferences(const char* file) {
    Preference* pref = (Preference*)malloc(sizeof(Preference));
    memcpy(pref, file, sizeof(Preference));
    printf("Preference Name: %s, Preference Value: %s\n", pref->pref_name, pref->pref_value);
    free(pref);
}

int main() {
    char file[sizeof(Preference)];
    memset(file, 0, sizeof(file));
    strcpy(file, "example_pref");
    strcpy(file + 50, "example_pref_value");

    import_preferences(file);
    return 0;
}