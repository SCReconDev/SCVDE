#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char preference_name[50];
    char preference_value[100];
} Preference;

void deserialize_preference(Preference *pref, const char *data) {
    sscanf(data, "%49s %99[^\n]", pref->preference_name, pref->preference_value);
}

void import_preferences(const char *data) {
    Preference pref;
    deserialize_preference(&pref, data);
    printf("Preference Name: %s, Value: %s\n", pref.preference_name, pref.preference_value);
}

int main() {
    char data[150];
    printf("Enter preference data: ");
    fgets(data, sizeof(data), stdin);
    import_preferences(data);
    return 0;
}