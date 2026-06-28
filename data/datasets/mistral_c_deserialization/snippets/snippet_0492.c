#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* preference_name;
    char* preference_value;
} Preference;

void import_preferences(char* user_file) {
    Preference* preference = (Preference*)malloc(sizeof(Preference));
    memcpy(preference, user_file, sizeof(Preference));
    printf("Preference: %s = %s\n", preference->preference_name, preference->preference_value);
    free(preference);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <user_file>\n", argv[0]);
        return 1;
    }
    import_preferences(argv[1]);
    return 0;
}