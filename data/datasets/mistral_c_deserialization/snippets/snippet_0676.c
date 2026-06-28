#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* plugin_name;
    int version;
} PluginConfig;

void load_plugin_config(PluginConfig* config) {
    printf("Plugin Name: %s, Version: %d\n", config->plugin_name, config->version);
}

int main() {
    const char* config_blob = "{\"plugin_name\":\"plugin1\",\"version\":1}";
    struct json_object* json_obj = json_tokener_parse(config_blob);

    if (json_obj == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    PluginConfig config;
    json_object_object_foreach(json_obj, key, val) {
        if (strcmp(key, "plugin_name") == 0) {
            config.plugin_name = strdup(json_object_get_string(val));
        } else if (strcmp(key, "version") == 0) {
            config.version = json_object_get_int(val);
        }
    }

    load_plugin_config(&config);
    free(config.plugin_name);
    json_object_put(json_obj);

    return 0;
}