#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char setting[50];
    int value;
} Setting;

void load_settings(Setting *setting, const char *file_data) {
    char *token = strtok((char *)file_data, ";");
    strcpy(setting->setting, token);
    token = strtok(NULL, ";");
    setting->value = atoi(token);
}

int main() {
    char file_data[100];
    Setting setting;

    printf("Enter file data: ");
    fgets(file_data, sizeof(file_data), stdin);

    load_settings(&setting, file_data);

    printf("Setting: Setting=%s, Value=%d\n", setting.setting, setting.value);

    return 0;
}