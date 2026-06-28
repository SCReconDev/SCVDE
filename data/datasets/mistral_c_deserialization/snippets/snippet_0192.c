#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} Preference;

void deserialize_preference(const char* file, Preference* pref) {
    char* token = strtok((char*)file, " ");
    pref->key = strdup(token);
    token = strtok(NULL, " ");
    pref->value = strdup(token);
}

int main() {
    char* file = "language en";
    Preference pref;
    deserialize_preference(file, &pref);
    printf("Key: %s, Value: %s\n", pref.key, pref.value);
    free(pref.key);
    free(pref.value);
    return 0;
}