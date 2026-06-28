#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char name[50];
    int age;
    char email[100];
} User;

int validate_user_json(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *name_obj, *age_obj, *email_obj;

    parsed_json = json_tokener_parse(json_str);
    if (!parsed_json) {
        return 0;
    }

    if (!json_object_object_get_ex(parsed_json, "name", &name_obj) ||
        !json_object_object_get_ex(parsed_json, "age", &age_obj) ||
        !json_object_object_get_ex(parsed_json, "email", &email_obj)) {
        json_object_put(parsed_json);
        return 0;
    }

    if (json_object_get_type(name_obj) != json_type_string ||
        json_object_get_type(age_obj) != json_type_int ||
        json_object_get_type(email_obj) != json_type_string) {
        json_object_put(parsed_json);
        return 0;
    }

    json_object_put(parsed_json);
    return 1;
}

User* deserialize_user(const char *json_str) {
    User *user = malloc(sizeof(User));
    if (!user) {
        return NULL;
    }

    struct json_object *parsed_json;
    struct json_object *name_obj, *age_obj, *email_obj;

    parsed_json = json_tokener_parse(json_str);
    if (!parsed_json) {
        free(user);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "name", &name_obj);
    json_object_object_get_ex(parsed_json, "age", &age_obj);
    json_object_object_get_ex(parsed_json, "email", &email_obj);

    strncpy(user->name, json_object_get_string(name_obj), sizeof(user->name) - 1);
    user->age = json_object_get_int(age_obj);
    strncpy(user->email, json_object_get_string(email_obj), sizeof(user->email) - 1);

    json_object_put(parsed_json);
    return user;
}

void process_user_data(const char *json_str) {
    if (!validate_user_json(json_str)) {
        printf("Invalid user data format\n");
        return;
    }

    User *user = deserialize_user(json_str);
    if (!user) {
        printf("Failed to deserialize user data\n");
        return;
    }

    printf("User: %s, Age: %d, Email: %s\n", user->name, user->age, user->email);
    free(user);
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    printf("Enter user data in JSON format:\n");
    fgets(buffer, sizeof(buffer), stdin);

    process_user_data(buffer);

    return 0;
}