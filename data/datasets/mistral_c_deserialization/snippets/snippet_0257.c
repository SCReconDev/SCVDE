#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* setting_name;
    int setting_value;
} Setting;

void deserialize_setting(char* data, Setting* setting) {
    char* token = strtok(data, ",");
    setting->setting_name = strdup(token);
    token = strtok(NULL, ",");
    setting->setting_value = atoi(token);
}

void import_file(char* state_file) {
    Setting setting;
    deserialize_setting(state_file, &setting);
    printf("Setting: %s, Value: %d\n", setting.setting_name, setting.setting_value);
    free(setting.setting_name);
}

int main() {
    char* state_file = "timeout,30";
    import_file(state_file);
    return 0;
}