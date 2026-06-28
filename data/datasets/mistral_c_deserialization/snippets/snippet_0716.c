#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* plugin_name;
    char* plugin_version;
    char* plugin_settings;
} PluginConfig;

void deserialize_plugin_config(const char* json_str, PluginConfig* config) {
    cJSON* json = cJSON_Parse(json_str);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* plugin_name = cJSON_GetObjectItemCaseSensitive(json, "plugin_name");
    if (cJSON_IsString(plugin_name) && (plugin_name->valuestring != NULL)) {
        config->plugin_name = strdup(plugin_name->valuestring);
    }

    cJSON* plugin_version = cJSON_GetObjectItemCaseSensitive(json, "plugin_version");
    if (cJSON_IsString(plugin_version) && (plugin_version->valuestring != NULL)) {
        config->plugin_version = strdup(plugin_version->valuestring);
    }

    cJSON* plugin_settings = cJSON_GetObjectItemCaseSensitive(json, "plugin_settings");
    if (cJSON_IsString(plugin_settings) && (plugin_settings->valuestring != NULL)) {
        config->plugin_settings = strdup(plugin_settings->valuestring);
    }

    cJSON_Delete(json);
}

int main() {
    const char* json_str = "{\"plugin_name\":\"example_plugin\",\"plugin_version\":\"1.0\",\"plugin_settings\":\"enabled=true\"}";
    PluginConfig config;

    deserialize_plugin_config(json_str, &config);

    printf("Plugin Name: %s\n", config.plugin_name);
    printf("Plugin Version: %s\n", config.plugin_version);
    printf("Plugin Settings: %s\n", config.plugin_settings);

    free(config.plugin_name);
    free(config.plugin_version);
    free(config.plugin_settings);

    return 0;
}