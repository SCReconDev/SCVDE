#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_CONFIG_SIZE 1024

typedef struct {
    char plugin_name[50];
    int version;
} PluginConfig;

int validate_plugin_config(json_object *jobj) {
    json_object *jplugin_name, *jversion;

    if (!json_object_object_get_ex(jobj, "plugin_name", &jplugin_name) ||
        !json_object_object_get_ex(jobj, "version", &jversion)) {
        return 0;
    }

    if (json_object_get_type(jplugin_name) != json_type_string ||
        json_object_get_type(jversion) != json_type_int) {
        return 0;
    }

    return 1;
}

PluginConfig* load_plugin_config(const char *config_blob) {
    json_object *jobj = json_tokener_parse(config_blob);
    if (jobj == NULL) {
        return NULL;
    }

    if (!validate_plugin_config(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    PluginConfig *config = (PluginConfig*)malloc(sizeof(PluginConfig));
    if (config == NULL) {
        json_object_put(jobj);
        return NULL;
    }

    strcpy(config->plugin_name, json_object_get_string(json_object_object_get(jobj, "plugin_name")));
    config->version = json_object_get_int(json_object_object_get(jobj, "version"));

    json_object_put(jobj);
    return config;
}

int main() {
    char config_blob[MAX_CONFIG_SIZE];
    printf("Enter plugin config blob: ");
    fgets(config_blob, MAX_CONFIG_SIZE, stdin);

    PluginConfig *config = load_plugin_config(config_blob);
    if (config != NULL) {
        printf("Plugin Name: %s\nVersion: %d\n", config->plugin_name, config->version);
        free(config);
    } else {
        printf("Invalid plugin config blob.\n");
    }

    return 0;
}