#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    char name[256];
    int age;
    char email[256];
} User;

void deserialize_user(User *user, const char *json_payload) {
    struct json_object *parsed_json;
    struct json_object *name_obj, *age_obj, *email_obj;

    parsed_json = json_tokener_parse(json_payload);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON payload\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "name", &name_obj);
    json_object_object_get_ex(parsed_json, "age", &age_obj);
    json_object_object_get_ex(parsed_json, "email", &email_obj);

    if (name_obj != NULL && json_object_is_type(name_obj, json_type_string)) {
        strncpy(user->name, json_object_get_string(name_obj), sizeof(user->name) - 1);
    }

    if (age_obj != NULL && json_object_is_type(age_obj, json_type_int)) {
        user->age = json_object_get_int(age_obj);
    }

    if (email_obj != NULL && json_object_is_type(email_obj, json_type_string)) {
        strncpy(user->email, json_object_get_string(email_obj), sizeof(user->email) - 1);
    }

    json_object_put(parsed_json);
}

int main() {
    User user;
    char payload[MAX_PAYLOAD_SIZE];

    printf("Enter JSON payload: ");
    fgets(payload, sizeof(payload), stdin);

    deserialize_user(&user, payload);

    printf("Deserialized User:\n");
    printf("Name: %s\n", user.name);
    printf("Age: %d\n", user.age);
    printf("Email: %s\n", user.email);

    return 0;
}