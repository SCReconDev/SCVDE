#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char username[50];
    char email[50];
} User;

void display_user(User *user) {
    printf("Username: %s\n", user->username);
    printf("Email: %s\n", user->email);
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    FILE *file = fopen("user.json", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fread(buffer, sizeof(char), MAX_BUFFER_SIZE, file);
    fclose(file);

    struct json_object *parsed_json = json_tokener_parse(buffer);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    struct json_object *username_obj, *email_obj;
    if (!json_object_object_get_ex(parsed_json, "username", &username_obj) ||
        !json_object_object_get_ex(parsed_json, "email", &email_obj)) {
        fprintf(stderr, "Error accessing JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    User user;
    strncpy(user.username, json_object_get_string(username_obj), sizeof(user.username) - 1);
    strncpy(user.email, json_object_get_string(email_obj), sizeof(user.email) - 1);

    display_user(&user);

    json_object_put(parsed_json);
    return 0;
}