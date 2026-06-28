#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *setting_name;
    char *setting_value;
    int is_default;
} Setting;

void update_setting(Setting *setting) {
    printf("Setting: %s, Value: %s, Default: %d\n", setting->setting_name, setting->setting_value, setting->is_default);
}

int main() {
    const char *json_str = "{\"setting_name\":\"Timeout\", \"setting_value\":\"30s\", \"is_default\":0}";
    struct json_object *parsed_json;
    struct json_object *setting_name_obj, *setting_value_obj, *is_default_obj;
    Setting setting;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    if (!json_object_object_get_ex(parsed_json, "setting_name", &setting_name_obj) ||
        !json_object_object_get_ex(parsed_json, "setting_value", &setting_value_obj) ||
        !json_object_object_get_ex(parsed_json, "is_default", &is_default_obj)) {
        fprintf(stderr, "Error extracting JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    setting.setting_name = strdup(json_object_get_string(setting_name_obj));
    setting.setting_value = strdup(json_object_get_string(setting_value_obj));
    setting.is_default = json_object_get_int(is_default_obj);

    update_setting(&setting);

    free(setting.setting_name);
    free(setting.setting_value);
    json_object_put(parsed_json);

    return 0;
}