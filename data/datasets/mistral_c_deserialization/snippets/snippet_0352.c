#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* pref_name;
    char* pref_value;
} Preference;

void deserialize_preference(const char* data, Preference* pref) {
    char* token = strtok((char*)data, "=");
    pref->pref_name = strdup(token);
    token = strtok(NULL, "=");
    pref->pref_value = strdup(token);
}

int main() {
    FILE* file = fopen("preferences.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char buffer[1024];
    fgets(buffer, sizeof(buffer), file);
    fclose(file);

    Preference pref;
    deserialize_preference(buffer, &pref);

    printf("Preference Name: %s, Value: %s\n", pref.pref_name, pref.pref_value);
    free(pref.pref_name);
    free(pref.pref_value);

    return 0;
}