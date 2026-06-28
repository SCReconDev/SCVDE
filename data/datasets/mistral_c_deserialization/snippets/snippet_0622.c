#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *username;
    char *email;
} User;

void deserialize_user(const char *json_str, User *user) {
    struct json_object *parsed_json;
    struct json_object *username;
    struct json_object *email;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "username", &username);
    json_object_object_get_ex(parsed_json, "email", &email);

    if (username != NULL && json_object_is_type(username, json_type_string)) {
        user->username = strdup(json_object_get_string(username));
    } else {
        user->username = NULL;
    }

    if (email != NULL && json_object_is_type(email, json_type_string)) {
        user->email = strdup(json_object_get_string(email));
    } else {
        user->email = NULL;
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"username\":\"johndoe\",\"email\":\"johndoe@example.com\"}";
    User user;

    deserialize_user(json_str, &user);

    printf("Username: %s\n", user.username);
    printf("Email: %s\n", user.email);

    free(user.username);
    free(user.email);
    return 0;
}