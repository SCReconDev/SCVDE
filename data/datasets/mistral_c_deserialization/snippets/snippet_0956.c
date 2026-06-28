#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *setting_name;
    char *setting_value;
} PluginSetting;

void load_plugin_settings(const char *blob, PluginSetting *settings, int *count) {
    struct json_object *parsed_json;
    struct json_object *settings_array;
    size_t i;

    parsed_json = json_tokener_parse(blob);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "settings", &settings_array)) {
        *count = json_object_array_length(settings_array);
        for (i = 0; i < *count; i++) {
            struct json_object *setting_obj = json_object_array_get_idx(settings_array, i);
            struct json_object *name_obj;
            struct json_object *value_obj;

            if (json_object_object_get_ex(setting_obj, "name", &name_obj)) {
                settings[i].setting_name = strdup(json_object_get_string(name_obj));
            }

            if (json_object_object_get_ex(setting_obj, "value", &value_obj)) {
                settings[i].setting_value = strdup(json_object_get_string(value_obj));
            }
        }
    }

    json_object_put(parsed_json);
}

int main() {
    const char *blob = "{\"settings\":[{\"name\":\"setting1\",\"value\":\"value1\"},{\"name\":\"setting2\",\"value\":\"value2\"}]}";
    PluginSetting settings[10];
    int count = 0;
    int i;

    load_plugin_settings(blob, settings, &count);

    for (i = 0; i < count; i++) {
        printf("Setting Name: %s, Setting Value: %s\n", settings[i].setting_name, settings[i].setting_value);
        free(settings[i].setting_name);
        free(settings[i].setting_value);
    }

    return 0;
}