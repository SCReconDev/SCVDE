#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *username;
    char *password;
} User;

void deserialize_user(const char *json_str, User *user) {
    struct json_object *parsed_json;
    struct json_object *username;
    struct json_object *password;

    parsed_json = json_tokener_parse(json_str);
    if (json_object_object_get_ex(parsed_json, "username", &username)) {
        user->username = strdup(json_object_get_string(username));
    }
    if (json_object_object_get_ex(parsed_json, "password", &password)) {
        user->password = strdup(json_object_get_string(password));
    }
    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"username\":\"admin\",\"password\":\"securepassword\"}";
    User user;

    deserialize_user(json_str, &user);

    printf("Username: %s\n", user.username);
    printf("Password: %s\n", user.password);

    free(user.username);
    free(user.password);
    return 0;
}