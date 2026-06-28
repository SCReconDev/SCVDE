#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>

typedef struct {
    char* plugin_name;
    char* config_value;
} PluginConfig;

bool validate_plugin_json(const char* json_str) {
    struct json_object* obj = json_tokener_parse(json_str);
    if (obj == NULL) {
        return false;
    }

    bool has_plugin_name = json_object_object_get_ex(obj, "plugin_name", NULL);
    bool has_config_value = json_object_object_get_ex(obj, "config_value", NULL);

    json_object_put(obj);
    return has_plugin_name && has_config_value;
}

PluginConfig* deserialize_plugin_config(const char* json_str) {
    if (!validate_plugin_json(json_str)) {
        return NULL;
    }

    struct json_object* obj = json_tokener_parse(json_str);
    PluginConfig* config = malloc(sizeof(PluginConfig));

    struct json_object* plugin_name_obj;
    json_object_object_get_ex(obj, "plugin_name", &plugin_name_obj);
    config->plugin_name = strdup(json_object_get_string(plugin_name_obj));

    struct json_object* config_value_obj;
    json_object_object_get_ex(obj, "config_value", &config_value_obj);
    config->config_value = strdup(json_object_get_string(config_value_obj));

    json_object_put(obj);
    return config;
}

void free_plugin_config(PluginConfig* config) {
    free(config->plugin_name);
    free(config->config_value);
    free(config);
}

void load_plugin_config(const char* json_str) {
    PluginConfig* config = deserialize_plugin_config(json_str);
    if (config == NULL) {
        printf("Invalid plugin config data\n");
        return;
    }

    printf("Plugin Name: %s, Config Value: %s\n", config->plugin_name, config->config_value);
    free_plugin_config(config);
}

int main() {
    const char* json_str = "{\"plugin_name\":\"logger\",\"config_value\":\"enabled\"}";
    load_plugin_config(json_str);
    return 0;
}