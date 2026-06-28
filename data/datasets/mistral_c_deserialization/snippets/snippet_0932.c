#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* username;
    char* password;
} UserCredentials;

void deserialize_credentials(const char* json_str, UserCredentials* credentials) {
    struct json_object* parsed_json;
    struct json_object* username;
    struct json_object* password;

    parsed_json = json_tokener_parse(json_str);

    if (json_object_object_get_ex(parsed_json, "username", &username)) {
        credentials->username = strdup(json_object_get_string(username));
    }

    if (json_object_object_get_ex(parsed_json, "password", &password)) {
        credentials->password = strdup(json_object_get_string(password));
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"username\":\"johndoe\",\"password\":\"securepassword123\"}";
    UserCredentials credentials;

    deserialize_credentials(json_str, &credentials);

    printf("Username: %s\n", credentials.username);
    printf("Password: %s\n", credentials.password);

    free(credentials.username);
    free(credentials.password);

    return 0;
}