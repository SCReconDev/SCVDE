#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* preference;
    char* value;
} Preference;

void import_preferences(const char* user_file) {
    Preference* pref = (Preference*)user_file;
    printf("Preference: %s, Value: %s\n", pref->preference, pref->value);
}

int main() {
    const char* user_file = "{\"preference\":\"theme\",\"value\":\"dark\"}";
    import_preferences(user_file);
    return 0;
}