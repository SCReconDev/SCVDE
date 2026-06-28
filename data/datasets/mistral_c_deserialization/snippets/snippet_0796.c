#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *plugin_name;
    int version;
} Plugin;

void load_plugin(Plugin *plugin) {
    printf("Loading plugin: %s\n", plugin->plugin_name);
    printf("Version: %d\n", plugin->version);
}

int main() {
    const char *config_blob = "{\"plugin_name\":\"analytics\",\"version\":1}";
    struct json_object *parsed_json;
    struct json_object *plugin_name;
    struct json_object *version;
    Plugin plugin;

    parsed_json = json_tokener_parse(config_blob);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    json_object_object_get_ex(parsed_json, "plugin_name", &plugin_name);
    json_object_object_get_ex(parsed_json, "version", &version);

    if (plugin_name == NULL || version == NULL) {
        fprintf(stderr, "Missing required fields in JSON\n");
        json_object_put(parsed_json);
        return 1;
    }

    plugin.plugin_name = strdup(json_object_get_string(plugin_name));
    plugin.version = json_object_get_int(version);

    load_plugin(&plugin);

    free(plugin.plugin_name);
    json_object_put(parsed_json);

    return 0;
}