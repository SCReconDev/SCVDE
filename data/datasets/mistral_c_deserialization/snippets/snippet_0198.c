#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* setting;
    int value;
} Setting;

void load_config(const char* config_blob) {
    Setting* setting = (Setting*)config_blob;
    printf("Setting: %s, Value: %d\n", setting->setting, setting->value);
}

int main() {
    const char* config_blob = "{\"setting\":\"timeout\",\"value\":30}";
    load_config(config_blob);
    return 0;
}