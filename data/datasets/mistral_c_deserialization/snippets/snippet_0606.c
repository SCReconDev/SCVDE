#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* setting_name;
    char* setting_value;
} PluginSetting;

void process_plugin_setting(PluginSetting* setting) {
    printf("Setting Name: %s\n", setting->setting_name);
    printf("Setting Value: %s\n", setting->setting_value);
}

PluginSetting* deserialize_plugin_setting(const char* json_str) {
    struct json_object* parsed_json;
    struct json_object* setting_name_obj;
    struct json_object* setting_value_obj;
    PluginSetting* setting = malloc(sizeof(PluginSetting));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        free(setting);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "setting_name", &setting_name_obj);
    json_object_object_get_ex(parsed_json, "setting_value", &setting_value_obj);

    if (setting_name_obj == NULL || setting_value_obj == NULL) {
        fprintf(stderr, "Invalid JSON format\n");
        json_object_put(parsed_json);
        free(setting);
        return NULL;
    }

    setting->setting_name = strdup(json_object_get_string(setting_name_obj));
    setting->setting_value = strdup(json_object_get_string(setting_value_obj));

    json_object_put(parsed_json);
    return setting;
}

int main() {
    const char* json_str = "{\"setting_name\":\"timeout\",\"setting_value\":\"30\"}";
    PluginSetting* setting = deserialize_plugin_setting(json_str);

    if (setting != NULL) {
        process_plugin_setting(setting);
        free(setting->setting_name);
        free(setting->setting_value);
        free(setting);
    }

    return 0;
}