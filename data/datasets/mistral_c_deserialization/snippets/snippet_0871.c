#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_INPUT_SIZE 1024

typedef struct {
    char name[256];
    int age;
    char email[256];
} User;

int validate_user(User *user) {
    if (strlen(user->name) == 0 || strlen(user->email) == 0 || user->age <= 0) {
        return 0;
    }
    return 1;
}

User* deserialize_user(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *name_obj, *age_obj, *email_obj;
    User *user = malloc(sizeof(User));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        free(user);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "name", &name_obj);
    json_object_object_get_ex(parsed_json, "age", &age_obj);
    json_object_object_get_ex(parsed_json, "email", &email_obj);

    if (name_obj == NULL || age_obj == NULL || email_obj == NULL) {
        json_object_put(parsed_json);
        free(user);
        return NULL;
    }

    strncpy(user->name, json_object_get_string(name_obj), sizeof(user->name) - 1);
    user->age = json_object_get_int(age_obj);
    strncpy(user->email, json_object_get_string(email_obj), sizeof(user->email) - 1);

    json_object_put(parsed_json);

    if (!validate_user(user)) {
        free(user);
        return NULL;
    }

    return user;
}

void process_user(User *user) {
    printf("Processing user: %s, %d, %s\n", user->name, user->age, user->email);
}

int main() {
    char input[MAX_INPUT_SIZE];
    User *user;

    printf("Enter user data in JSON format: ");
    fgets(input, sizeof(input), stdin);

    user = deserialize_user(input);
    if (user == NULL) {
        printf("Invalid user data\n");
        return 1;
    }

    process_user(user);

    free(user);
    return 0;
}