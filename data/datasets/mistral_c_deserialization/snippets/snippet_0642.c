#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* username;
    char* email;
} User;

void display_user(User* user) {
    printf("Username: %s\n", user->username);
    printf("Email: %s\n", user->email);
}

int main() {
    const char* json_str = "{\"username\":\"john_doe\",\"email\":\"john@example.com\"}";
    struct json_object* parsed_json;
    struct json_object* username;
    struct json_object* email;
    User user;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    json_object_object_get_ex(parsed_json, "username", &username);
    json_object_object_get_ex(parsed_json, "email", &email);

    if (username == NULL || email == NULL) {
        fprintf(stderr, "Invalid JSON structure\n");
        json_object_put(parsed_json);
        return 1;
    }

    user.username = strdup(json_object_get_string(username));
    user.email = strdup(json_object_get_string(email));

    display_user(&user);

    free(user.username);
    free(user.email);
    json_object_put(parsed_json);

    return 0;
}