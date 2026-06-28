#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char plugin_id[50];
    char plugin_name[100];
    char plugin_config[200];
} Plugin;

int validate_plugin_json(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *plugin_id_obj, *plugin_name_obj, *plugin_config_obj;

    parsed_json = json_tokener_parse(json_str);
    if (!parsed_json) {
        return 0;
    }

    if (!json_object_object_get_ex(parsed_json, "plugin_id", &plugin_id_obj) ||
        !json_object_object_get_ex(parsed_json, "plugin_name", &plugin_name_obj) ||
        !json_object_object_get_ex(parsed_json, "plugin_config", &plugin_config_obj)) {
        json_object_put(parsed_json);
        return 0;
    }

    if (json_object_get_type(plugin_id_obj) != json_type_string ||
        json_object_get_type(plugin_name_obj) != json_type_string ||
        json_object_get_type(plugin_config_obj) != json_type_string) {
        json_object_put(parsed_json);
        return 0;
    }

    json_object_put(parsed_json);
    return 1;
}

Plugin* deserialize_plugin(const char *json_str) {
    Plugin *plugin = malloc(sizeof(Plugin));
    if (!plugin) {
        return NULL;
    }

    struct json_object *parsed_json;
    struct json_object *plugin_id_obj, *plugin_name_obj, *plugin_config_obj;

    parsed_json = json_tokener_parse(json_str);
    if (!parsed_json) {
        free(plugin);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "plugin_id", &plugin_id_obj);
    json_object_object_get_ex(parsed_json, "plugin_name", &plugin_name_obj);
    json_object_object_get_ex(parsed_json, "plugin_config", &plugin_config_obj);

    strncpy(plugin->plugin_id, json_object_get_string(plugin_id_obj), sizeof(plugin->plugin_id) - 1);
    strncpy(plugin->plugin_name, json_object_get_string(plugin_name_obj), sizeof(plugin->plugin_name) - 1);
    strncpy(plugin->plugin_config, json_object_get_string(plugin_config_obj), sizeof(plugin->plugin_config) - 1);

    json_object_put(parsed_json);
    return plugin;
}

void process_plugin_data(const char *json_str) {
    if (!validate_plugin_json(json_str)) {
        printf("Invalid plugin data format\n");
        return;
    }

    Plugin *plugin = deserialize_plugin(json_str);
    if (!plugin) {
        printf("Failed to deserialize plugin data\n");
        return;
    }

    printf("Plugin ID: %s, Plugin Name: %s, Plugin Config: %s\n", plugin->plugin_id, plugin->plugin_name, plugin->plugin_config);
    free(plugin);
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    printf("Enter plugin data in JSON format:\n");
    fgets(buffer, sizeof(buffer), stdin);

    process_plugin_data(buffer);

    return 0;
}