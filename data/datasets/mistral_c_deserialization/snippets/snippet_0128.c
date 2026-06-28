#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONFIG_SIZE 1024

void load_config(const char *blob) {
    char *decoded_blob = (char *)malloc(CONFIG_SIZE);
    if (decoded_blob == NULL) {
        return;
    }

    size_t decoded_length = CONFIG_SIZE;
    if (base64_decode(blob, decoded_blob, &decoded_length) != 0) {
        free(decoded_blob);
        return;
    }

    void *config_data = deserialize_config(decoded_blob, decoded_length);
    if (config_data == NULL) {
        free(decoded_blob);
        return;
    }

    printf("Configuration loaded successfully.\n");

    free(config_data);
    free(decoded_blob);
}

int main() {
    char blob[CONFIG_SIZE];
    printf("Enter configuration blob: ");
    fgets(blob, CONFIG_SIZE, stdin);
    blob[strcspn(blob, "\n")] = '\0';

    load_config(blob);

    return 0;
}