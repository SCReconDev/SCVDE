#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int value;
} Setting;

void deserialize_setting(Setting* setting, const char* data) {
    char* token = strtok((char*)data, "=");
    setting->name = strdup(token);
    token = strtok(NULL, "=");
    setting->value = atoi(token);
}

void import_file(const char* file_data) {
    Setting setting;
    deserialize_setting(&setting, file_data);
    printf("Name: %s, Value: %d\n", setting.name, setting.value);
    free(setting.name);
}

int main() {
    const char* file_data = "timeout=30";
    import_file(file_data);
    return 0;
}