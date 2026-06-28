#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char plugin_id[50];
    char plugin_name[50];
    char plugin_version[50];
} PluginInfo;

int validate_plugin_info(PluginInfo *plugin_info) {
    if (strlen(plugin_info->plugin_id) == 0 || strlen(plugin_info->plugin_name) == 0 || strlen(plugin_info->plugin_version) == 0) {
        return 0;
    }
    return 1;
}

PluginInfo* deserialize_plugin_info(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *plugin_id_obj, *plugin_name_obj, *plugin_version_obj;
    PluginInfo *plugin_info = (PluginInfo*)malloc(sizeof(PluginInfo));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        free(plugin_info);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "plugin_id", &plugin_id_obj);
    json_object_object_get_ex(parsed_json, "plugin_name", &plugin_name_obj);
    json_object_object_get_ex(parsed_json, "plugin_version", &plugin_version_obj);

    if (plugin_id_obj == NULL || plugin_name_obj == NULL || plugin_version_obj == NULL) {
        json_object_put(parsed_json);
        free(plugin_info);
        return NULL;
    }

    strncpy(plugin_info->plugin_id, json_object_get_string(plugin_id_obj), sizeof(plugin_info->plugin_id) - 1);
    strncpy(plugin_info->plugin_name, json_object_get_string(plugin_name_obj), sizeof(plugin_info->plugin_name) - 1);
    strncpy(plugin_info->plugin_version, json_object_get_string(plugin_version_obj), sizeof(plugin_info->plugin_version) - 1);

    json_object_put(parsed_json);

    if (!validate_plugin_info(plugin_info)) {
        free(plugin_info);
        return NULL;
    }

    return plugin_info;
}

void process_plugin_info(PluginInfo *plugin_info) {
    printf("Plugin ID: %s\n", plugin_info->plugin_id);
    printf("Plugin Name: %s\n", plugin_info->plugin_name);
    printf("Plugin Version: %s\n", plugin_info->plugin_version);
}

int main() {
    char json_str[MAX_BUFFER_SIZE];
    PluginInfo *plugin_info;

    printf("Enter plugin info data in JSON format:\n");
    fgets(json_str, MAX_BUFFER_SIZE, stdin);

    plugin_info = deserialize_plugin_info(json_str);
    if (plugin_info == NULL) {
        printf("Invalid plugin info data\n");
        return 1;
    }

    process_plugin_info(plugin_info);
    free(plugin_info);

    return 0;
}