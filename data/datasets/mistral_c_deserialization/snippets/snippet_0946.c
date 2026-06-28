#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* plugin_name;
    char* plugin_config;
} PluginConfig;

void parse_plugin_config(const char* config) {
    cJSON* json = cJSON_Parse(config);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* plugin_name = cJSON_GetObjectItemCaseSensitive(json, "plugin_name");
    cJSON* plugin_config = cJSON_GetObjectItemCaseSensitive(json, "plugin_config");

    if (cJSON_IsString(plugin_name) && (plugin_name->valuestring != NULL)) {
        printf("Plugin Name: %s\n", plugin_name->valuestring);
    }

    if (cJSON_IsString(plugin_config) && (plugin_config->valuestring != NULL)) {
        printf("Plugin Config: %s\n", plugin_config->valuestring);
    }

    cJSON_Delete(json);
}

int main() {
    const char* config = "{\"plugin_name\":\"example_plugin\",\"plugin_config\":\"{\\\"setting1\\\":\\\"value1\\\"}\"}";
    parse_plugin_config(config);
    return 0;
}