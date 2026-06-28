#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int value;
} Setting;

void load_settings(const char* state) {
    Setting setting;
    char* decoded = strdup(state);
    char* token = strtok(decoded, "=");
    setting.name = strdup(token);
    token = strtok(NULL, "=");
    setting.value = atoi(token);
    printf("Setting loaded: %s = %d\n", setting.name, setting.value);
    free(setting.name);
    free(decoded);
}

int main() {
    const char* state = "volume=75";
    load_settings(state);
    return 0;
}