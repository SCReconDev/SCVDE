#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *username;
    char *email;
} User;

void display_user(User *user) {
    printf("Username: %s, Email: %s\n", user->username, user->email);
}

int main() {
    const char *json_str = "{\"username\":\"johndoe\", \"email\":\"john@example.com\"}";
    struct json_object *parsed_json;
    struct json_object *username_obj, *email_obj;
    User user;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    if (!json_object_object_get_ex(parsed_json, "username", &username_obj) ||
        !json_object_object_get_ex(parsed_json, "email", &email_obj)) {
        fprintf(stderr, "Error extracting JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    user.username = strdup(json_object_get_string(username_obj));
    user.email = strdup(json_object_get_string(email_obj));

    display_user(&user);

    free(user.username);
    free(user.email);
    json_object_put(parsed_json);

    return 0;
}