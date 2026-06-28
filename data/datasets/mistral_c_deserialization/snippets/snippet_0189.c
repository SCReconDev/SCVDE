#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} ConfigEntry;

void load_config(const char* input, ConfigEntry* entry) {
    char* token = strtok((char*)input, "=");
    entry->key = strdup(token);
    token = strtok(NULL, "=");
    entry->value = strdup(token);
}

int main() {
    char* input = "theme=dark";
    ConfigEntry entry;
    load_config(input, &entry);
    printf("Key: %s, Value: %s\n", entry.key, entry.value);
    free(entry.key);
    free(entry.value);
    return 0;
}