#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int value;
} Preference;

void load_preference(Preference* preference, const char* data) {
    char* token = strtok((char*)data, ":");
    preference->name = strdup(token);
    token = strtok(NULL, ":");
    preference->value = atoi(token);
}

void restore_command(const char* input) {
    Preference preference;
    load_preference(&preference, input);
    printf("Name: %s, Value: %d\n", preference.name, preference.value);
    free(preference.name);
}

int main() {
    const char* input = "theme:dark";
    restore_command(input);
    return 0;
}