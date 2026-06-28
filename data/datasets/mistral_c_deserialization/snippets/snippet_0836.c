#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* setting;
    int value;
} PluginSetting;

void deserialize_plugin_setting(const char* json_str, PluginSetting* setting) {
    struct json_object* parsed_json;
    struct json_object* setting_name;
    struct json_object* value;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "setting", &setting_name);
    json_object_object_get_ex(parsed_json, "value", &value);

    if (setting_name != NULL && json_object_get_type(setting_name) == json_type_string) {
        setting->setting = strdup(json_object_get_string(setting_name));
    }

    if (value != NULL && json_object_get_type(value) == json_type_int) {
        setting->value = json_object_get_int(value);
    }

    json_object_put(parsed_json);
}

void load_plugin_settings(const char* config_blob) {
    PluginSetting setting = {NULL, 0};
    deserialize_plugin_setting(config_blob, &setting);

    if (setting.setting != NULL) {
        printf("Setting: %s\n", setting.setting);
        free(setting.setting);
    }

    printf("Value: %d\n", setting.value);
}

int main() {
    const char* config_blob = "{\"setting\":\"timeout\",\"value\":30}";
    load_plugin_settings(config_blob);
    return 0;
}