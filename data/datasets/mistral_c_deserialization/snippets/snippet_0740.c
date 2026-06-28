#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char preference_name[50];
    char preference_value[200];
} Preference;

bool validate_preference(Preference* preference) {
    if (strlen(preference->preference_name) == 0 || strlen(preference->preference_value) == 0) {
        return false;
    }
    return true;
}

void import_preference(Preference* preference) {
    if (validate_preference(preference)) {
        printf("Preference imported: %s, %s\n", preference->preference_name, preference->preference_value);
    } else {
        printf("Invalid preference data\n");
    }
}

int main() {
    Preference preference1 = {"example_preference", "{\"setting1\": \"value1\", \"setting2\": \"value2\"}"};
    Preference preference2 = {"", "{\"setting1\": \"value1\", \"setting2\": \"value2\"}"};

    import_preference(&preference1);
    import_preference(&preference2);

    return 0;
}