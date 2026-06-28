#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char setting[256];
    int value;
} Setting;

void deserialize_setting(Setting *setting, const char *data) {
    sscanf(data, "%255[^;];%d", setting->setting, &setting->value);
}

void load_plugin_settings(const char *blob) {
    Setting setting;
    deserialize_setting(&setting, blob);
    printf("Setting: %s = %d\n", setting.setting, setting.value);
}

int main() {
    char blob[512];
    printf("Enter settings blob: ");
    fgets(blob, sizeof(blob), stdin);
    load_plugin_settings(blob);
    return 0;
}