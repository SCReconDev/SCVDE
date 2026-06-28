#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

typedef struct {
    char* username;
    char* email;
} User;

bool validate_user_schema(const cJSON* json) {
    if (!cJSON_IsObject(json)) return false;
    cJSON* username = cJSON_GetObjectItemCaseSensitive(json, "username");
    cJSON* email = cJSON_GetObjectItemCaseSensitive(json, "email");
    if (!cJSON_IsString(username) || !cJSON_IsString(email)) return false;
    return true;
}

User* deserialize_user(const char* json_str) {
    cJSON* json = cJSON_Parse(json_str);
    if (!json || !validate_user_schema(json)) {
        cJSON_Delete(json);
        return NULL;
    }

    User* user = malloc(sizeof(User));
    if (!user) {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON* username = cJSON_GetObjectItemCaseSensitive(json, "username");
    cJSON* email = cJSON_GetObjectItemCaseSensitive(json, "email");

    user->username = strdup(username->valuestring);
    user->email = strdup(email->valuestring);

    cJSON_Delete(json);
    return user;
}

void free_user(User* user) {
    if (user) {
        free(user->username);
        free(user->email);
        free(user);
    }
}

int main() {
    const char* json_str = "{\"username\":\"johndoe\",\"email\":\"john.doe@example.com\"}";
    User* user = deserialize_user(json_str);

    if (user) {
        printf("Username: %s\nEmail: %s\n", user->username, user->email);
        free_user(user);
    } else {
        printf("Failed to deserialize user.\n");
    }

    return 0;
}