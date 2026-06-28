#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* preference_name;
    char* preference_value;
} UserPreference;

void parse_user_file(const char* file_content) {
    struct json_object* parsed_json;
    struct json_object* preference_name;
    struct json_object* preference_value;

    parsed_json = json_tokener_parse(file_content);

    if (json_object_object_get_ex(parsed_json, "preference_name", &preference_name)) {
        UserPreference* preference = (UserPreference*)malloc(sizeof(UserPreference));
        preference->preference_name = strdup(json_object_get_string(preference_name));

        if (json_object_object_get_ex(parsed_json, "preference_value", &preference_value)) {
            preference->preference_value = strdup(json_object_get_string(preference_value));
        } else {
            preference->preference_value = strdup("");
        }

        printf("Preference Name: %s, Preference Value: %s\n", preference->preference_name, preference->preference_value);
        free(preference->preference_name);
        free(preference->preference_value);
        free(preference);
    }

    json_object_put(parsed_json);
}

int main() {
    const char* file_content = "{\"preference_name\":\"theme\",\"preference_value\":\"dark\"}";
    parse_user_file(file_content);
    return 0;
}