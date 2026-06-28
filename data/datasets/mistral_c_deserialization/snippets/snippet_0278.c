#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* value;
} Setting;

void load_settings(Setting* setting, const char* blob) {
    char* token = strtok((char*)blob, "=");
    setting->name = strdup(token);
    token = strtok(NULL, "=");
    setting->value = strdup(token);
}

int main() {
    char blob[100];
    printf("Enter settings blob: ");
    fgets(blob, sizeof(blob), stdin);
    blob[strcspn(blob, "\n")] = 0;

    Setting setting;
    load_settings(&setting, blob);

    printf("Name: %s, Value: %s\n", setting.name, setting.value);
    free(setting.name);
    free(setting.value);
    return 0;
}