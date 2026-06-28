#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *username;
    char *email;
} User;

void display_user(User *user) {
    printf("Username: %s\n", user->username);
    printf("Email: %s\n", user->email);
}

int main() {
    const char *cookie_value = "{\"username\":\"johndoe\",\"email\":\"john@example.com\"}";
    struct json_object *parsed_json;
    struct json_object *username;
    struct json_object *email;
    User user;

    parsed_json = json_tokener_parse(cookie_value);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    json_object_object_get_ex(parsed_json, "username", &username);
    json_object_object_get_ex(parsed_json, "email", &email);

    if (username == NULL || email == NULL) {
        fprintf(stderr, "Missing required fields in JSON\n");
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