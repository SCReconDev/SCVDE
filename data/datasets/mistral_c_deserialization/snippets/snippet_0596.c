#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *config_name;
    int timeout;
    char *log_level;
} Config;

void parse_config_data(const char *json_str, Config *config) {
    struct json_object *parsed_json;
    struct json_object *name_obj;
    struct json_object *timeout_obj;
    struct json_object *log_level_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "config_name", &name_obj)) {
        config->config_name = strdup(json_object_get_string(name_obj));
    }

    if (json_object_object_get_ex(parsed_json, "timeout", &timeout_obj)) {
        config->timeout = json_object_get_int(timeout_obj);
    }

    if (json_object_object_get_ex(parsed_json, "log_level", &log_level_obj)) {
        config->log_level = strdup(json_object_get_string(log_level_obj));
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"config_name\":\"default\",\"timeout\":30,\"log_level\":\"info\"}";
    Config config;

    parse_config_data(json_str, &config);

    printf("Config Name: %s\n", config.config_name);
    printf("Timeout: %d\n", config.timeout);
    printf("Log Level: %s\n", config.log_level);

    free(config.config_name);
    free(config.log_level);
    return 0;
}