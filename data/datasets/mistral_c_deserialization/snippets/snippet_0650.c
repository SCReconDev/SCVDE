#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* setting_name;
    char* setting_value;
    int is_default;
} Setting;

void display_setting(Setting* setting) {
    printf("Setting Name: %s\n", setting->setting_name);
    printf("Setting Value: %s\n", setting->setting_value);
    printf("Is Default: %d\n", setting->is_default);
}

int main() {
    const char* json_str = "{\"setting_name\":\"Timeout\",\"setting_value\":\"30\",\"is_default\":1}";
    struct json_object* parsed_json;
    struct json_object* setting_name;
    struct json_object* setting_value;
    struct json_object* is_default;
    Setting setting;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    json_object_object_get_ex(parsed_json, "setting_name", &setting_name);
    json_object_object_get_ex(parsed_json, "setting_value", &setting_value);
    json_object_object_get_ex(parsed_json, "is_default", &is_default);

    if (setting_name == NULL || setting_value == NULL || is_default == NULL) {
        fprintf(stderr, "Invalid JSON structure\n");
        json_object_put(parsed_json);
        return 1;
    }

    setting.setting_name = strdup(json_object_get_string(setting_name));
    setting.setting_value = strdup(json_object_get_string(setting_value));
    setting.is_default = json_object_get_int(is_default);

    display_setting(&setting);

    free(setting.setting_name);
    free(setting.setting_value);
    json_object_put(parsed_json);

    return 0;
}