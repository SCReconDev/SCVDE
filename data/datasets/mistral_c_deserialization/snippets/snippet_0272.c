#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char pref_name[50];
    char pref_value[100];
} Preference;

void deserialize_preference(Preference *pref, const char *data) {
    char *token = strtok((char *)data, ":");
    if (token != NULL) {
        strncpy(pref->pref_name, token, sizeof(pref->pref_name) - 1);
        token = strtok(NULL, ":");
        if (token != NULL) {
            strncpy(pref->pref_value, token, sizeof(pref->pref_value) - 1);
        }
    }
}

int main() {
    char data[150];
    Preference pref;

    printf("Enter preference data: ");
    fgets(data, sizeof(data), stdin);

    deserialize_preference(&pref, data);

    printf("Deserialized Preference: Preference Name=%s, Preference Value=%s\n", pref.pref_name, pref.pref_value);

    return 0;
}