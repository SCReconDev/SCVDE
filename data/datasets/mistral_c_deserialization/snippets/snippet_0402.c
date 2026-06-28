#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* preference_name;
    char* preference_value;
} Preference;

void import_preference(Preference* pref) {
    printf("Preference Name: %s\n", pref->preference_name);
    printf("Preference Value: %s\n", pref->preference_value);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <user_file>\n", argv[0]);
        return 1;
    }

    char* user_file = argv[1];
    Preference* pref = (Preference*)user_file;
    import_preference(pref);

    return 0;
}