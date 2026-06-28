#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* setting_name;
    char* setting_value;
} Setting;

void restore_settings(char* input_file) {
    Setting* setting = (Setting*)malloc(sizeof(Setting));
    memcpy(setting, input_file, sizeof(Setting));
    printf("Setting: %s = %s\n", setting->setting_name, setting->setting_value);
    free(setting);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    restore_settings(argv[1]);
    return 0;
}