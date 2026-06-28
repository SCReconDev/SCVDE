#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char pref_name[50];
    char pref_value[100];
} UserPreference;

void deserialize_preference(const char* data, UserPreference* pref) {
    sscanf(data, "%49s %99[^\n]", pref->pref_name, pref->pref_value);
}

void load_preference(const char* data) {
    UserPreference pref;
    deserialize_preference(data, &pref);
    printf("Preference: %s, Value: %s\n", pref.pref_name, pref.pref_value);
}

int main() {
    char data[200];
    printf("Enter preference data: ");
    fgets(data, sizeof(data), stdin);
    load_preference(data);
    return 0;
}