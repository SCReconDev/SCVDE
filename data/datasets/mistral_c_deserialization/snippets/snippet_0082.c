#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char setting_name[50];
    char setting_value[200];
} Setting;

void deserialize_setting(Setting *setting, const char *data) {
    sscanf(data, "%49s %199[^\n]", setting->setting_name, setting->setting_value);
}

void import_preferences(const char *data) {
    Setting setting;
    deserialize_setting(&setting, data);
    printf("Imported setting: %s, value: %s\n", setting.setting_name, setting.setting_value);
}

int main() {
    char data[300];
    printf("Enter user file content: ");
    fgets(data, sizeof(data), stdin);
    import_preferences(data);
    return 0;
}