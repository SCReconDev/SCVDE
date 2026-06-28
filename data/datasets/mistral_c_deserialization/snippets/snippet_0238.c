#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} Config;

void load_config(Config* config, const char* data) {
    char* token = strtok((char*)data, "=");
    config->key = strdup(token);
    token = strtok(NULL, "=");
    config->value = strdup(token);
}

int main() {
    FILE* file = fopen("config_data.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        perror("Error reading file");
        fclose(file);
        return 1;
    }

    Config config;
    load_config(&config, buffer);

    printf("Key: %s, Value: %s\n", config.key, config.value);

    free(config.key);
    free(config.value);
    fclose(file);
    return 0;
}