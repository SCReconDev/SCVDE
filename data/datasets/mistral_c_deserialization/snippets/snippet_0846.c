#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_CONFIG_SIZE 1024

typedef struct {
    char setting_name[50];
    char setting_value[100];
} PluginSetting;

void load_plugin_settings(const char *config_blob) {
    struct json_object *parsed_json;
    struct json_object *settings_array;
    size_t i, array_length;
    PluginSetting setting;

    parsed_json = json_tokener_parse(config_blob);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing config blob\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "settings", &settings_array)) {
        fprintf(stderr, "Invalid config format\n");
        json_object_put(parsed_json);
        return;
    }

    array_length = json_object_array_length(settings_array);
    for (i = 0; i < array_length; i++) {
        struct json_object *setting_obj = json_object_array_get_idx(settings_array, i);
        struct json_object *name_obj, *value_obj;

        if (!json_object_object_get_ex(setting_obj, "name", &name_obj) ||
            !json_object_object_get_ex(setting_obj, "value", &value_obj)) {
            continue;
        }

        strncpy(setting.setting_name, json_object_get_string(name_obj), sizeof(setting.setting_name) - 1);
        strncpy(setting.setting_value, json_object_get_string(value_obj), sizeof(setting.setting_value) - 1);

        printf("Setting - Name: %s, Value: %s\n", setting.setting_name, setting.setting_value);
    }

    json_object_put(parsed_json);
}

int main() {
    char config[MAX_CONFIG_SIZE];
    printf("Enter config blob: ");
    fgets(config, sizeof(config), stdin);

    load_plugin_settings(config);

    return 0;
}