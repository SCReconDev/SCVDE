#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *config_name;
    int config_value;
} Config;

void restore_config(const char *file_path, Config *configs, int *count) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Error allocating memory\n");
        fclose(file);
        return;
    }

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    struct json_object *parsed_json;
    struct json_object *configs_array;
    size_t i;

    parsed_json = json_tokener_parse(buffer);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        free(buffer);
        return;
    }

    if (json_object_object_get_ex(parsed_json, "configs", &configs_array)) {
        *count = json_object_array_length(configs_array);
        for (i = 0; i < *count; i++) {
            struct json_object *config_obj = json_object_array_get_idx(configs_array, i);
            struct json_object *name_obj;
            struct json_object *value_obj;

            if (json_object_object_get_ex(config_obj, "name", &name_obj)) {
                configs[i].config_name = strdup(json_object_get_string(name_obj));
            }

            if (json_object_object_get_ex(config_obj, "value", &value_obj)) {
                configs[i].config_value = json_object_get_int(value_obj);
            }
        }
    }

    json_object_put(parsed_json);
    free(buffer);
}

int main() {
    const char *file_path = "config.json";
    Config configs[10];
    int count = 0;
    int i;

    restore_config(file_path, configs, &count);

    for (i = 0; i < count; i++) {
        printf("Config Name: %s, Config Value: %d\n", configs[i].config_name, configs[i].config_value);
        free(configs[i].config_name);
    }

    return 0;
}