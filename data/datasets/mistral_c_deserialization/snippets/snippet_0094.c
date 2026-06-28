#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char preference[50];
    int setting;
} Preference;

void load_preference(Preference *preference, const char *file_data) {
    char *token = strtok((char *)file_data, " ");
    strcpy(preference->preference, token);
    token = strtok(NULL, " ");
    preference->setting = atoi(token);
}

int main() {
    char file_data[100];
    Preference preference;

    printf("Enter file data: ");
    fgets(file_data, sizeof(file_data), stdin);

    load_preference(&preference, file_data);

    printf("Preference: Preference=%s, Setting=%d\n", preference.preference, preference.setting);

    return 0;
}