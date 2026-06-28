#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int value;
} Preference;

void deserialize_preference(Preference* preference, const char* data) {
    char* token = strtok((char*)data, " ");
    preference->name = strdup(token);
    token = strtok(NULL, " ");
    preference->value = atoi(token);
}

void import_preferences(const char* file_data) {
    Preference preference;
    deserialize_preference(&preference, file_data);
    printf("Name: %s, Value: %d\n", preference.name, preference.value);
    free(preference.name);
}

int main() {
    const char* file_data = "volume 50";
    import_preferences(file_data);
    return 0;
}