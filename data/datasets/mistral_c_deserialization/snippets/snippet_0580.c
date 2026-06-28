#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>

typedef struct {
    char *ticket_id;
    char *subject;
    char *status;
} Ticket;

bool validate_ticket_schema(const json_object *jobj) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "ticket_id") == 0 && json_object_get_type(val) != json_type_string) {
            return false;
        }
        if (strcmp(key, "subject") == 0 && json_object_get_type(val) != json_type_string) {
            return false;
        }
        if (strcmp(key, "status") == 0 && json_object_get_type(val) != json_type_string) {
            return false;
        }
    }
    return true;
}

Ticket *deserialize_ticket(const char *json_str) {
    json_object *jobj = json_tokener_parse(json_str);
    if (!jobj) {
        return NULL;
    }

    if (!validate_ticket_schema(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Ticket *ticket = malloc(sizeof(Ticket));
    if (!ticket) {
        json_object_put(jobj);
        return NULL;
    }

    json_object *ticket_id_obj, *subject_obj, *status_obj;
    if (json_object_object_get_ex(jobj, "ticket_id", &ticket_id_obj)) {
        ticket->ticket_id = strdup(json_object_get_string(ticket_id_obj));
    } else {
        ticket->ticket_id = NULL;
    }

    if (json_object_object_get_ex(jobj, "subject", &subject_obj)) {
        ticket->subject = strdup(json_object_get_string(subject_obj));
    } else {
        ticket->subject = NULL;
    }

    if (json_object_object_get_ex(jobj, "status", &status_obj)) {
        ticket->status = strdup(json_object_get_string(status_obj));
    } else {
        ticket->status = NULL;
    }

    json_object_put(jobj);
    return ticket;
}

void free_ticket(Ticket *ticket) {
    if (ticket) {
        free(ticket->ticket_id);
        free(ticket->subject);
        free(ticket->status);
        free(ticket);
    }
}

int main() {
    const char *json_str = "{\"ticket_id\":\"33445\",\"subject\":\"Technical Issue\",\"status\":\"Open\"}";
    Ticket *ticket = deserialize_ticket(json_str);

    if (ticket) {
        printf("Ticket ID: %s\n", ticket->ticket_id);
        printf("Subject: %s\n", ticket->subject);
        printf("Status: %s\n", ticket->status);
        free_ticket(ticket);
    } else {
        printf("Failed to deserialize ticket.\n");
    }

    return 0;
}