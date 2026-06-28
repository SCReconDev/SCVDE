#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} Setting;

void load_setting(const char* data, Setting* setting) {
    char* token = strtok((char*)data, ":");
    setting->key = strdup(token);
    token = strtok(NULL, ":");
    setting->value = strdup(token);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char buffer[1024];
    fgets(buffer, sizeof(buffer), file);
    fclose(file);

    Setting setting;
    load_setting(buffer, &setting);

    printf("Key: %s, Value: %s\n", setting.key, setting.value);
    free(setting.key);
    free(setting.value);

    return 0;
}