#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char setting_name[50];
    int setting_value;
} PluginSetting;

void deserialize_setting(PluginSetting *setting, const char *blob) {
    sscanf(blob, "%49s %d", setting->setting_name, &setting->setting_value);
}

void load_settings(const char *blob) {
    PluginSetting setting;
    deserialize_setting(&setting, blob);
    printf("Setting Name: %s, Setting Value: %d\n", setting.setting_name, setting.setting_value);
}

int main() {
    char blob[100];
    printf("Enter blob: ");
    fgets(blob, sizeof(blob), stdin);
    load_settings(blob);
    return 0;
}