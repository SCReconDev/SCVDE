#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* plugin_name;
    int version;
} PluginConfig;

void deserialize_plugin_config(const char* json_str, PluginConfig* config) {
    struct json_object* parsed_json;
    struct json_object* name_obj;
    struct json_object* version_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "name", &name_obj);
    json_object_object_get_ex(parsed_json, "version", &version_obj);

    if (name_obj != NULL && json_object_is_type(name_obj, json_type_string)) {
        config->plugin_name = strdup(json_object_get_string(name_obj));
    }

    if (version_obj != NULL && json_object_is_type(version_obj, json_type_int)) {
        config->version = json_object_get_int(version_obj);
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"name\":\"example_plugin\",\"version\":1}";
    PluginConfig config;

    deserialize_plugin_config(json_str, &config);

    printf("Plugin Name: %s\n", config.plugin_name);
    printf("Version: %d\n", config.version);

    free(config.plugin_name);
    return 0;
}