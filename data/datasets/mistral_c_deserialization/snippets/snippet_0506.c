#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* plugin_name;
    char* config;
} PluginConfig;

void load_plugin_config(const char* config_blob) {
    cJSON* json = cJSON_Parse(config_blob);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* plugin_name = cJSON_GetObjectItemCaseSensitive(json, "plugin_name");
    cJSON* config = cJSON_GetObjectItemCaseSensitive(json, "config");

    if (cJSON_IsString(plugin_name) && (plugin_name->valuestring != NULL) && cJSON_IsString(config) && (config->valuestring != NULL)) {
        PluginConfig plugin;
        plugin.plugin_name = strdup(plugin_name->valuestring);
        plugin.config = strdup(config->valuestring);

        printf("Plugin: %s, Config: %s\n", plugin.plugin_name, plugin.config);

        free(plugin.plugin_name);
        free(plugin.config);
    }

    cJSON_Delete(json);
}

int main() {
    const char* config_blob = "{\"plugin_name\":\"logger\",\"config\":\"enabled\"}";
    load_plugin_config(config_blob);
    return 0;
}