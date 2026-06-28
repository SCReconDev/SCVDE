#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} Preference;

void restore_preferences(const char* input) {
    Preference pref;
    char* decoded = strdup(input);
    char* token = strtok(decoded, ":");
    pref.key = strdup(token);
    token = strtok(NULL, ":");
    pref.value = strdup(token);
    printf("Preference restored: %s = %s\n", pref.key, pref.value);
    free(pref.key);
    free(pref.value);
    free(decoded);
}

int main() {
    const char* input = "theme:dark";
    restore_preferences(input);
    return 0;
}