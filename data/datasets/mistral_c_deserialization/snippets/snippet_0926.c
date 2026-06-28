#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *plugin_name;
    char *version;
    int enabled;
} Plugin;

void configure_plugin(Plugin *plugin) {
    printf("Plugin: %s, Version: %s, Enabled: %d\n", plugin->plugin_name, plugin->version, plugin->enabled);
}

int main() {
    const char *json_str = "{\"plugin_name\":\"Analytics\", \"version\":\"1.0.0\", \"enabled\":1}";
    struct json_object *parsed_json;
    struct json_object *plugin_name_obj, *version_obj, *enabled_obj;
    Plugin plugin;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    if (!json_object_object_get_ex(parsed_json, "plugin_name", &plugin_name_obj) ||
        !json_object_object_get_ex(parsed_json, "version", &version_obj) ||
        !json_object_object_get_ex(parsed_json, "enabled", &enabled_obj)) {
        fprintf(stderr, "Error extracting JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    plugin.plugin_name = strdup(json_object_get_string(plugin_name_obj));
    plugin.version = strdup(json_object_get_string(version_obj));
    plugin.enabled = json_object_get_int(enabled_obj);

    configure_plugin(&plugin);

    free(plugin.plugin_name);
    free(plugin.version);
    json_object_put(parsed_json);

    return 0;
}