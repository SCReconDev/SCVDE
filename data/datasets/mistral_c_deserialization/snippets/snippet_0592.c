#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *username;
    char *email;
} User;

void parse_user_data(const char *json_str, User *user) {
    struct json_object *parsed_json;
    struct json_object *username_obj;
    struct json_object *email_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "username", &username_obj)) {
        user->username = strdup(json_object_get_string(username_obj));
    }

    if (json_object_object_get_ex(parsed_json, "email", &email_obj)) {
        user->email = strdup(json_object_get_string(email_obj));
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"username\":\"johndoe\",\"email\":\"john.doe@example.com\"}";
    User user;

    parse_user_data(json_str, &user);

    printf("Username: %s\n", user.username);
    printf("Email: %s\n", user.email);

    free(user.username);
    free(user.email);
    return 0;
}