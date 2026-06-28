#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

typedef struct {
    char* name;
    int age;
    char* email;
} User;

bool validate_user_schema(cJSON* json) {
    if (!cJSON_HasObjectItem(json, "name") ||
        !cJSON_HasObjectItem(json, "age") ||
        !cJSON_HasObjectItem(json, "email")) {
        return false;
    }

    cJSON* name = cJSON_GetObjectItemCaseSensitive(json, "name");
    cJSON* age = cJSON_GetObjectItemCaseSensitive(json, "age");
    cJSON* email = cJSON_GetObjectItemCaseSensitive(json, "email");

    if (!cJSON_IsString(name) || !cJSON_IsNumber(age) || !cJSON_IsString(email)) {
        return false;
    }

    return true;
}

User* deserialize_user(const char* json_str) {
    cJSON* json = cJSON_Parse(json_str);
    if (!json) {
        return NULL;
    }

    if (!validate_user_schema(json)) {
        cJSON_Delete(json);
        return NULL;
    }

    User* user = (User*)malloc(sizeof(User));
    if (!user) {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON* name = cJSON_GetObjectItemCaseSensitive(json, "name");
    cJSON* age = cJSON_GetObjectItemCaseSensitive(json, "age");
    cJSON* email = cJSON_GetObjectItemCaseSensitive(json, "email");

    user->name = strdup(name->valuestring);
    user->age = age->valueint;
    user->email = strdup(email->valuestring);

    cJSON_Delete(json);

    return user;
}

void free_user(User* user) {
    if (user) {
        free(user->name);
        free(user->email);
        free(user);
    }
}

int main() {
    const char* json_str = "{\"name\":\"John Doe\",\"age\":30,\"email\":\"john.doe@example.com\"}";
    User* user = deserialize_user(json_str);

    if (user) {
        printf("Name: %s\n", user->name);
        printf("Age: %d\n", user->age);
        printf("Email: %s\n", user->email);
        free_user(user);
    } else {
        printf("Failed to deserialize user.\n");
    }

    return 0;
}