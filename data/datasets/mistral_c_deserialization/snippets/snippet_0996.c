#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_CONFIG_SIZE 1024

typedef struct {
    char plugin_id[256];
    int plugin_version;
    char plugin_settings[256];
} PluginConfig;

void deserialize_plugin_config(PluginConfig *config, const char *config_blob) {
    struct json_object *parsed_json;
    struct json_object *plugin_id_obj, *plugin_version_obj, *plugin_settings_obj;

    parsed_json = json_tokener_parse(config_blob);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON config blob\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "plugin_id", &plugin_id_obj);
    json_object_object_get_ex(parsed_json, "plugin_version", &plugin_version_obj);
    json_object_object_get_ex(parsed_json, "plugin_settings", &plugin_settings_obj);

    if (plugin_id_obj != NULL && json_object_is_type(plugin_id_obj, json_type_string)) {
        strncpy(config->plugin_id, json_object_get_string(plugin_id_obj), sizeof(config->plugin_id) - 1);
    }

    if (plugin_version_obj != NULL && json_object_is_type(plugin_version_obj, json_type_int)) {
        config->plugin_version = json_object_get_int(plugin_version_obj);
    }

    if (plugin_settings_obj != NULL && json_object_is_type(plugin_settings_obj, json_type_string)) {
        strncpy(config->plugin_settings, json_object_get_string(plugin_settings_obj), sizeof(config->plugin_settings) - 1);
    }

    json_object_put(parsed_json);
}

int main() {
    PluginConfig config;
    char config_blob[MAX_CONFIG_SIZE];

    printf("Enter config blob: ");
    fgets(config_blob, sizeof(config_blob), stdin);

    deserialize_plugin_config(&config, config_blob);

    printf("Deserialized Plugin Config:\n");
    printf("Plugin ID: %s\n", config.plugin_id);
    printf("Plugin Version: %d\n", config.plugin_version);
    printf("Plugin Settings: %s\n", config.plugin_settings);

    return 0;
}