#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_COOKIE_SIZE 256

typedef struct {
    char username[50];
    char session_id[50];
} Session;

int validate_session(json_object *jobj) {
    json_object *jusername, *jsession_id;

    if (!json_object_object_get_ex(jobj, "username", &jusername) ||
        !json_object_object_get_ex(jobj, "session_id", &jsession_id)) {
        return 0;
    }

    if (json_object_get_type(jusername) != json_type_string ||
        json_object_get_type(jsession_id) != json_type_string) {
        return 0;
    }

    return 1;
}

Session* load_session(const char *cookie) {
    json_object *jobj = json_tokener_parse(cookie);
    if (jobj == NULL) {
        return NULL;
    }

    if (!validate_session(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Session *session = (Session*)malloc(sizeof(Session));
    if (session == NULL) {
        json_object_put(jobj);
        return NULL;
    }

    strcpy(session->username, json_object_get_string(json_object_object_get(jobj, "username")));
    strcpy(session->session_id, json_object_get_string(json_object_object_get(jobj, "session_id")));

    json_object_put(jobj);
    return session;
}

int main() {
    char cookie[MAX_COOKIE_SIZE];
    printf("Enter session cookie: ");
    fgets(cookie, MAX_COOKIE_SIZE, stdin);

    Session *session = load_session(cookie);
    if (session != NULL) {
        printf("Username: %s\nSession ID: %s\n", session->username, session->session_id);
        free(session);
    } else {
        printf("Invalid session cookie.\n");
    }

    return 0;
}