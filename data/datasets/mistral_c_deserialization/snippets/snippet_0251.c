#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* preference_name;
    char* preference_value;
} Preference;

Preference* deserialize_preference(const char* file) {
    FILE* fp = fopen(file, "r");
    char buffer[1024];
    fgets(buffer, sizeof(buffer), fp);
    fclose(fp);

    Preference* pref = malloc(sizeof(Preference));
    char* token = strtok(buffer, "=");
    pref->preference_name = strdup(token);
    token = strtok(NULL, "=");
    pref->preference_value = strdup(token);
    return pref;
}

void load_preference(const char* file) {
    Preference* pref = deserialize_preference(file);
    printf("Preference: %s\n", pref->preference_name);
    free(pref->preference_name);
    free(pref->preference_value);
    free(pref);
}

int main() {
    load_preference("preferences.txt");
    return 0;
}