#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *name;
    char *address;
    char *phone;
} Contact;

void deserialize_contact(const char *json_str, Contact *contact) {
    struct json_object *parsed_json;
    struct json_object *name;
    struct json_object *address;
    struct json_object *phone;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "name", &name);
    json_object_object_get_ex(parsed_json, "address", &address);
    json_object_object_get_ex(parsed_json, "phone", &phone);

    if (name != NULL && json_object_is_type(name, json_type_string)) {
        contact->name = strdup(json_object_get_string(name));
    } else {
        contact->name = NULL;
    }

    if (address != NULL && json_object_is_type(address, json_type_string)) {
        contact->address = strdup(json_object_get_string(address));
    } else {
        contact->address = NULL;
    }

    if (phone != NULL && json_object_is_type(phone, json_type_string)) {
        contact->phone = strdup(json_object_get_string(phone));
    } else {
        contact->phone = NULL;
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"name\":\"Jane Doe\",\"address\":\"123 Main St\",\"phone\":\"555-1234\"}";
    Contact contact;

    deserialize_contact(json_str, &contact);

    printf("Name: %s\n", contact.name);
    printf("Address: %s\n", contact.address);
    printf("Phone: %s\n", contact.phone);

    free(contact.name);
    free(contact.address);
    free(contact.phone);
    return 0;
}