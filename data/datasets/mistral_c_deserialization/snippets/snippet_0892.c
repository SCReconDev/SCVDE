#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char username[50];
    char email[50];
} User;

int validate_user_schema(json_object *jobj) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "username") == 0 && !json_object_is_type(val, json_type_string)) {
            return 0;
        }
        if (strcmp(key, "email") == 0 && !json_object_is_type(val, json_type_string)) {
            return 0;
        }
    }
    return 1;
}

User* deserialize_user(const char *json_str) {
    json_object *jobj = json_tokener_parse(json_str);
    if (!jobj) {
        return NULL;
    }

    if (!validate_user_schema(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    User *user = (User*)malloc(sizeof(User));
    if (!user) {
        json_object_put(jobj);
        return NULL;
    }

    json_object *jusername = json_object_object_get(jobj, "username");
    json_object *jemail = json_object_object_get(jobj, "email");

    strcpy(user->username, json_object_get_string(jusername));
    strcpy(user->email, json_object_get_string(jemail));

    json_object_put(jobj);
    return user;
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    printf("Enter JSON string: ");
    fgets(buffer, MAX_BUFFER_SIZE, stdin);

    User *user = deserialize_user(buffer);
    if (user) {
        printf("Username: %s, Email: %s\n", user->username, user->email);
        free(user);
    } else {
        printf("Invalid JSON or schema\n");
    }

    return 0;
}