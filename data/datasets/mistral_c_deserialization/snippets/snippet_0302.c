#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* preference_name;
    int setting;
} Preference;

void import_preferences(const char* user_file) {
    Preference* pref = (Preference*)malloc(sizeof(Preference));
    memcpy(pref, user_file, sizeof(Preference));

    printf("Preference: %s, Setting: %d\n", pref->preference_name, pref->setting);
    free(pref);
}

int main() {
    char* user_pref_file = "theme\01";
    import_preferences(user_pref_file);
    return 0;
}