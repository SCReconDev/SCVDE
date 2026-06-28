#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* pref_name;
    char* pref_value;
} UserPreference;

void import_preference(UserPreference* pref) {
    printf("Importing preference: %s = %s\n", pref->pref_name, pref->pref_value);
}

int main() {
    char* user_file = "{\"pref_name\":\"theme\",\"pref_value\":\"dark\"}";
    UserPreference* pref = (UserPreference*)malloc(sizeof(UserPreference));
    memcpy(pref, user_file, sizeof(UserPreference));
    import_preference(pref);
    free(pref);
    return 0;
}