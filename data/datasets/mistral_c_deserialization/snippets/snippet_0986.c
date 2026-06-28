#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *plugin_name;
    int version;
} PluginInfo;

void deserialize_plugin_info(const char *json_str, PluginInfo *info) {
    struct json_object *parsed_json;
    struct json_object *plugin_name;
    struct json_object *version;

    parsed_json = json_tokener_parse(json_str);

    if (json_object_object_get_ex(parsed_json, "plugin_name", &plugin_name)) {
        info->plugin_name = strdup(json_object_get_string(plugin_name));
    }

    if (json_object_object_get_ex(parsed_json, "version", &version)) {
        info->version = json_object_get_int(version);
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"plugin_name\":\"text_editor\",\"version\":1}";
    PluginInfo info;

    deserialize_plugin_info(json_str, &info);

    printf("Plugin Name: %s\n", info.plugin_name);
    printf("Version: %d\n", info.version);

    free(info.plugin_name);

    return 0;
}