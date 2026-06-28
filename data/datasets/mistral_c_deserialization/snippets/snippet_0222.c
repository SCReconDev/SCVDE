#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char pref_name[50];
    int pref_value;
} Preference;

void import_preferences(char* user_file) {
    Preference* pref = (Preference*)malloc(sizeof(Preference));
    memcpy(pref, user_file, sizeof(Preference));
    printf("Preference imported: %s = %d\n", pref->pref_name, pref->pref_value);
    free(pref);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <user_file>\n", argv[0]);
        return 1;
    }

    char* user_file = argv[1];
    import_preferences(user_file);

    return 0;
}