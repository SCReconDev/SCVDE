#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_INPUT_SIZE 1024

typedef struct {
    char plugin_id[256];
    char plugin_name[256];
    char plugin_config[256];
} Plugin;

int validate_plugin(Plugin *plugin) {
    if (strlen(plugin->plugin_id) == 0 || strlen(plugin->plugin_name) == 0 || strlen(plugin->plugin_config) == 0) {
        return 0;
    }
    return 1;
}

Plugin* deserialize_plugin(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *plugin_id_obj, *plugin_name_obj, *plugin_config_obj;
    Plugin *plugin = malloc(sizeof(Plugin));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        free(plugin);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "plugin_id", &plugin_id_obj);
    json_object_object_get_ex(parsed_json, "plugin_name", &plugin_name_obj);
    json_object_object_get_ex(parsed_json, "plugin_config", &plugin_config_obj);

    if (plugin_id_obj == NULL || plugin_name_obj == NULL || plugin_config_obj == NULL) {
        json_object_put(parsed_json);
        free(plugin);
        return NULL;
    }

    strncpy(plugin->plugin_id, json_object_get_string(plugin_id_obj), sizeof(plugin->plugin_id) - 1);
    strncpy(plugin->plugin_name, json_object_get_string(plugin_name_obj), sizeof(plugin->plugin_name) - 1);
    strncpy(plugin->plugin_config, json_object_get_string(plugin_config_obj), sizeof(plugin->plugin_config) - 1);

    json_object_put(parsed_json);

    if (!validate_plugin(plugin)) {
        free(plugin);
        return NULL;
    }

    return plugin;
}

void process_plugin(Plugin *plugin) {
    printf("Processing plugin: %s, %s, %s\n", plugin->plugin_id, plugin->plugin_name, plugin->plugin_config);
}

int main() {
    char input[MAX_INPUT_SIZE];
    Plugin *plugin;

    printf("Enter plugin data in JSON format: ");
    fgets(input, sizeof(input), stdin);

    plugin = deserialize_plugin(input);
    if (plugin == NULL) {
        printf("Invalid plugin data\n");
        return 1;
    }

    process_plugin(plugin);

    free(plugin);
    return 0;
}