#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    char value[100];
} KeyValuePair;

void load_key_value_pair(KeyValuePair *pair, const char *data) {
    char *token = strtok((char *)data, "=");
    if (token != NULL) {
        strncpy(pair->key, token, sizeof(pair->key) - 1);
        token = strtok(NULL, "=");
        if (token != NULL) {
            strncpy(pair->value, token, sizeof(pair->value) - 1);
        }
    }
}

int main() {
    char data[150];
    KeyValuePair pair;

    printf("Enter key-value pair: ");
    fgets(data, sizeof(data), stdin);

    load_key_value_pair(&pair, data);

    printf("Loaded Key-Value Pair: Key=%s, Value=%s\n", pair.key, pair.value);

    return 0;
}