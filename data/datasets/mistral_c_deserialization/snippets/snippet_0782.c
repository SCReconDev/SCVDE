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
    struct json_object *username_obj, *email_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "username", &username_obj) ||
        !json_object_object_get_ex(parsed_json, "email", &email_obj)) {
        fprintf(stderr, "Error: Missing required fields\n");
        json_object_put(parsed_json);
        return;
    }

    if (json_object_get_type(username_obj) != json_type_string ||
        json_object_get_type(email_obj) != json_type_string) {
        fprintf(stderr, "Error: Invalid field types\n");
        json_object_put(parsed_json);
        return;
    }

    user->username = strdup(json_object_get_string(username_obj));
    user->email = strdup(json_object_get_string(email_obj));

    json_object_put(parsed_json);
}

void process_user(User *user) {
    printf("Username: %s\n", user->username);
    printf("Email: %s\n", user->email);
}

int main() {
    const char *json_str = "{\"username\": \"johndoe\", \"email\": \"john.doe@example.com\"}";
    User user;

    deserialize_user(json_str, &user);
    process_user(&user);

    free(user.username);
    free(user.email);
    return 0;
}