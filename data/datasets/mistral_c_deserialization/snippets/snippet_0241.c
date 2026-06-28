#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} Preference;

void deserialize_preference(Preference* pref, const char* data) {
    char* token = strtok((char*)data, ":");
    pref->key = strdup(token);
    token = strtok(NULL, ":");
    pref->value = strdup(token);
}

int main() {
    FILE* file = fopen("preference_data.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        perror("Error reading file");
        fclose(file);
        return 1;
    }

    Preference pref;
    deserialize_preference(&pref, buffer);

    printf("Key: %s, Value: %s\n", pref.key, pref.value);

    free(pref.key);
    free(pref.value);
    fclose(file);
    return 0;
}