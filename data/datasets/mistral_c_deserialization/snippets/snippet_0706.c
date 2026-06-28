#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char plugin_name[50];
    char config_data[255];
} PluginConfig;

bool validate_plugin_config(PluginConfig* config) {
    if (strlen(config->plugin_name) == 0 || strlen(config->plugin_name) >= 50) {
        return false;
    }
    if (strlen(config->config_data) >= 255) {
        return false;
    }
    return true;
}

void process_plugin_config(PluginConfig* config) {
    if (validate_plugin_config(config)) {
        printf("Plugin Name: %s, Config Data: %s\n", config->plugin_name, config->config_data);
    } else {
        printf("Invalid plugin config data\n");
    }
}

int main() {
    PluginConfig config1 = {"example_plugin", "{\"setting1\": \"value1\", \"setting2\": \"value2\"}"};
    PluginConfig config2 = {"", "{\"invalid\": \"data\"}"};

    process_plugin_config(&config1);
    process_plugin_config(&config2);

    return 0;
}