#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>

typedef struct {
    char *username;
    char *email;
} User;

bool validate_user_schema(const json_object *jobj) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "username") == 0 && json_object_get_type(val) != json_type_string) {
            return false;
        }
        if (strcmp(key, "email") == 0 && json_object_get_type(val) != json_type_string) {
            return false;
        }
    }
    return true;
}

User *deserialize_user(const char *json_str) {
    json_object *jobj = json_tokener_parse(json_str);
    if (!jobj) {
        return NULL;
    }

    if (!validate_user_schema(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    User *user = malloc(sizeof(User));
    if (!user) {
        json_object_put(jobj);
        return NULL;
    }

    json_object *username_obj, *email_obj;
    if (json_object_object_get_ex(jobj, "username", &username_obj)) {
        user->username = strdup(json_object_get_string(username_obj));
    } else {
        user->username = NULL;
    }

    if (json_object_object_get_ex(jobj, "email", &email_obj)) {
        user->email = strdup(json_object_get_string(email_obj));
    } else {
        user->email = NULL;
    }

    json_object_put(jobj);
    return user;
}

void free_user(User *user) {
    if (user) {
        free(user->username);
        free(user->email);
        free(user);
    }
}

int main() {
    const char *json_str = "{\"username\":\"johndoe\",\"email\":\"john.doe@example.com\"}";
    User *user = deserialize_user(json_str);

    if (user) {
        printf("Username: %s\n", user->username);
        printf("Email: %s\n", user->email);
        free_user(user);
    } else {
        printf("Failed to deserialize user.\n");
    }

    return 0;
}