#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *plugin_name;
    int version;
} PluginConfig;

void parse_plugin_config(json_object *jobj, PluginConfig *config) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "plugin_name") == 0) {
            config->plugin_name = strdup(json_object_get_string(val));
        } else if (strcmp(key, "version") == 0) {
            config->version = json_object_get_int(val);
        }
    }
}

int main() {
    const char *config_blob = "{\"plugin_name\":\"plugin1\",\"version\":1}";
    json_object *jobj = json_tokener_parse(config_blob);

    if (jobj == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    PluginConfig config;
    parse_plugin_config(jobj, &config);

    printf("Plugin Name: %s\n", config.plugin_name);
    printf("Version: %d\n", config.version);

    free(config.plugin_name);
    json_object_put(jobj);

    return 0;
}