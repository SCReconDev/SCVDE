#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char plugin_name[50];
    int enabled;
} PluginConfig;

int deserialize_plugin_config(const char* json_str, PluginConfig* config) {
    struct json_object *parsed_json;
    struct json_object *plugin_name_obj, *enabled_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return -1;
    }

    if (!json_object_object_get_ex(parsed_json, "plugin_name", &plugin_name_obj)) {
        fprintf(stderr, "Error getting plugin_name\n");
        json_object_put(parsed_json);
        return -1;
    }

    if (!json_object_object_get_ex(parsed_json, "enabled", &enabled_obj)) {
        fprintf(stderr, "Error getting enabled\n");
        json_object_put(parsed_json);
        return -1;
    }

    strncpy(config->plugin_name, json_object_get_string(plugin_name_obj), sizeof(config->plugin_name) - 1);
    config->enabled = json_object_get_int(enabled_obj);

    json_object_put(parsed_json);
    return 0;
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    PluginConfig config;

    printf("Enter plugin config JSON: ");
    fgets(buffer, sizeof(buffer), stdin);

    if (deserialize_plugin_config(buffer, &config) == 0) {
        printf("Deserialized Plugin Config: Name=%s, Enabled=%d\n", config.plugin_name, config.enabled);
    } else {
        fprintf(stderr, "Failed to deserialize plugin config\n");
    }

    return 0;
}