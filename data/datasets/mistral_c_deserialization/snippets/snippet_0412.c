#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* setting_name;
    int setting_value;
} Setting;

void import_setting(const char* file_content, Setting* setting) {
    char* token = strtok((char*)file_content, "=");
    setting->setting_name = strdup(token);
    token = strtok(NULL, "=");
    setting->setting_value = atoi(token);
}

int main() {
    char* file_content = "max_connections=50";
    Setting setting;
    import_setting(file_content, &setting);
    printf("Setting Name: %s, Value: %d\n", setting.setting_name, setting.setting_value);
    free(setting.setting_name);
    return 0;
}