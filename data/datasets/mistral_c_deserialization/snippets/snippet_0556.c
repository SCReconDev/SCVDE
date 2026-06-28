#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* plugin_name;
    int version;
} PluginSettings;

void parse_config_blob(const char* blob) {
    struct json_object* parsed_json;
    struct json_object* plugin_name;
    struct json_object* version;

    parsed_json = json_tokener_parse(blob);

    if (json_object_object_get_ex(parsed_json, "plugin_name", &plugin_name)) {
        PluginSettings* settings = (PluginSettings*)malloc(sizeof(PluginSettings));
        settings->plugin_name = strdup(json_object_get_string(plugin_name));

        if (json_object_object_get_ex(parsed_json, "version", &version)) {
            settings->version = json_object_get_int(version);
        } else {
            settings->version = 0;
        }

        printf("Plugin Name: %s, Version: %d\n", settings->plugin_name, settings->version);
        free(settings->plugin_name);
        free(settings);
    }

    json_object_put(parsed_json);
}

int main() {
    const char* blob = "{\"plugin_name\":\"example_plugin\",\"version\":1}";
    parse_config_blob(blob);
    return 0;
}