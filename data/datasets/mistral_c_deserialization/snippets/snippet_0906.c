#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* plugin_name;
    int version;
} PluginConfig;

void load_plugin(PluginConfig* config) {
    printf("Loading plugin: %s version: %d\n", config->plugin_name, config->version);
}

int main() {
    const char* config_blob = "{\"plugin_name\":\"logger\",\"version\":2}";
    cJSON* json = cJSON_Parse(config_blob);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return EXIT_FAILURE;
    }

    PluginConfig config;
    cJSON* plugin_name = cJSON_GetObjectItemCaseSensitive(json, "plugin_name");
    if (cJSON_IsString(plugin_name) && (plugin_name->valuestring != NULL)) {
        config.plugin_name = strdup(plugin_name->valuestring);
    } else {
        fprintf(stderr, "Invalid plugin name in config blob\n");
        cJSON_Delete(json);
        return EXIT_FAILURE;
    }

    cJSON* version = cJSON_GetObjectItemCaseSensitive(json, "version");
    if (cJSON_IsNumber(version)) {
        config.version = version->valueint;
    } else {
        fprintf(stderr, "Invalid version in config blob\n");
        free(config.plugin_name);
        cJSON_Delete(json);
        return EXIT_FAILURE;
    }

    load_plugin(&config);
    free(config.plugin_name);
    cJSON_Delete(json);
    return EXIT_SUCCESS;
}