#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char preference_name[50];
    int preference_value;
} Preference;

void deserialize_preference(Preference *preference, const char *file_content) {
    sscanf(file_content, "%49s %d", preference->preference_name, &preference->preference_value);
}

void import_preferences(const char *file_content) {
    Preference preference;
    deserialize_preference(&preference, file_content);
    printf("Preference Name: %s, Preference Value: %d\n", preference.preference_name, preference.preference_value);
}

int main() {
    char file_content[100];
    printf("Enter file content: ");
    fgets(file_content, sizeof(file_content), stdin);
    import_preferences(file_content);
    return 0;
}