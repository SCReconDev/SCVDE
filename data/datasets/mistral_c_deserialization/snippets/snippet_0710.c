#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char pref_name[50];
    char pref_value[255];
} Preference;

bool validate_preference(Preference* pref) {
    if (strlen(pref->pref_name) == 0 || strlen(pref->pref_name) >= 50) {
        return false;
    }
    if (strlen(pref->pref_value) >= 255) {
        return false;
    }
    return true;
}

void process_preference(Preference* pref) {
    if (validate_preference(pref)) {
        printf("Preference Name: %s, Value: %s\n", pref->pref_name, pref->pref_value);
    } else {
        printf("Invalid preference data\n");
    }
}

int main() {
    Preference pref1 = {"theme", "dark"};
    Preference pref2 = {"", "invalid"};

    process_preference(&pref1);
    process_preference(&pref2);

    return 0;
}