#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* plugin_name;
    char* version;
    int enabled;
} Plugin;

void print_plugin(Plugin* plugin) {
    printf("Plugin Name: %s\n", plugin->plugin_name);
    printf("Version: %s\n", plugin->version);
    printf("Enabled: %d\n", plugin->enabled);
}

int main() {
    const char* json_str = "{\"plugin_name\":\"Security Plugin\",\"version\":\"1.0.0\",\"enabled\":1}";
    struct json_object* parsed_json;
    struct json_object* plugin_name;
    struct json_object* version;
    struct json_object* enabled;
    Plugin plugin;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    json_object_object_get_ex(parsed_json, "plugin_name", &plugin_name);
    json_object_object_get_ex(parsed_json, "version", &version);
    json_object_object_get_ex(parsed_json, "enabled", &enabled);

    if (plugin_name == NULL || version == NULL || enabled == NULL) {
        fprintf(stderr, "Invalid JSON structure\n");
        json_object_put(parsed_json);
        return 1;
    }

    plugin.plugin_name = strdup(json_object_get_string(plugin_name));
    plugin.version = strdup(json_object_get_string(version));
    plugin.enabled = json_object_get_int(enabled);

    print_plugin(&plugin);

    free(plugin.plugin_name);
    free(plugin.version);
    json_object_put(parsed_json);

    return 0;
}