#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} Config;

void load_config(char* blob) {
    Config* config = (Config*)malloc(sizeof(Config));
    memcpy(config, blob, sizeof(Config));
    printf("Config: %s = %s\n", config->key, config->value);
    free(config);
}

int main() {
    char blob[1024];
    fgets(blob, sizeof(blob), stdin);
    load_config(blob);
    return 0;
}