#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char pref_name[50];
    char value[100];
} Preference;

void import_preferences(const char* user_file) {
    Preference* pref = (Preference*)malloc(sizeof(Preference));
    memcpy(pref, user_file, sizeof(Preference));
    printf("Preference: %s, Value: %s\n", pref->pref_name, pref->value);
    free(pref);
}

int main() {
    char user_file[200];
    printf("Enter user file: ");
    fgets(user_file, sizeof(user_file), stdin);
    import_preferences(user_file);
    return 0;
}