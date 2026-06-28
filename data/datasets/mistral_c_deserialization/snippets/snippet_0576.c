#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>

typedef struct {
    char *config_id;
    char *config_name;
    int config_value;
} Config;

bool validate_config_schema(const json_object *jobj) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "config_id") == 0 && json_object_get_type(val) != json_type_string) {
            return false;
        }
        if (strcmp(key, "config_name") == 0 && json_object_get_type(val) != json_type_string) {
            return false;
        }
        if (strcmp(key, "config_value") == 0 && json_object_get_type(val) != json_type_int) {
            return false;
        }
    }
    return true;
}

Config *deserialize_config(const char *json_str) {
    json_object *jobj = json_tokener_parse(json_str);
    if (!jobj) {
        return NULL;
    }

    if (!validate_config_schema(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Config *config = malloc(sizeof(Config));
    if (!config) {
        json_object_put(jobj);
        return NULL;
    }

    json_object *config_id_obj, *config_name_obj, *config_value_obj;
    if (json_object_object_get_ex(jobj, "config_id", &config_id_obj)) {
        config->config_id = strdup(json_object_get_string(config_id_obj));
    } else {
        config->config_id = NULL;
    }

    if (json_object_object_get_ex(jobj, "config_name", &config_name_obj)) {
        config->config_name = strdup(json_object_get_string(config_name_obj));
    } else {
        config->config_name = NULL;
    }

    if (json_object_object_get_ex(jobj, "config_value", &config_value_obj)) {
        config->config_value = json_object_get_int(config_value_obj);
    } else {
        config->config_value = 0;
    }

    json_object_put(jobj);
    return config;
}

void free_config(Config *config) {
    if (config) {
        free(config->config_id);
        free(config->config_name);
        free(config);
    }
}

int main() {
    const char *json_str = "{\"config_id\":\"98765\",\"config_name\":\"Timeout\",\"config_value\":30}";
    Config *config = deserialize_config(json_str);

    if (config) {
        printf("Config ID: %s\n", config->config_id);
        printf("Config Name: %s\n", config->config_name);
        printf("Config Value: %d\n", config->config_value);
        free_config(config);
    } else {
        printf("Failed to deserialize config.\n");
    }

    return 0;
}