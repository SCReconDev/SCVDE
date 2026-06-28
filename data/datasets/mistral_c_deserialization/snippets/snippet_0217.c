#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char setting_name[50];
    int setting_value;
} Setting;

void import_file(char* state_file) {
    Setting* setting = (Setting*)malloc(sizeof(Setting));
    memcpy(setting, state_file, sizeof(Setting));
    printf("Setting imported: %s = %d\n", setting->setting_name, setting->setting_value);
    free(setting);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <uploaded_state_file>\n", argv[0]);
        return 1;
    }

    char* state_file = argv[1];
    import_file(state_file);

    return 0;
}