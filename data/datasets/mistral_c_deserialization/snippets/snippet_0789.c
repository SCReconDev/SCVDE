#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *ticket_id;
    char *ticket_status;
} Ticket;

void deserialize_ticket(const char *json_str, Ticket *ticket) {
    struct json_object *parsed_json;
    struct json_object *ticket_id_obj, *ticket_status_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "ticket_id", &ticket_id_obj) ||
        !json_object_object_get_ex(parsed_json, "ticket_status", &ticket_status_obj)) {
        fprintf(stderr, "Error: Missing required fields\n");
        json_object_put(parsed_json);
        return;
    }

    if (json_object_get_type(ticket_id_obj) != json_type_string ||
        json_object_get_type(ticket_status_obj) != json_type_string) {
        fprintf(stderr, "Error: Invalid field types\n");
        json_object_put(parsed_json);
        return;
    }

    ticket->ticket_id = strdup(json_object_get_string(ticket_id_obj));
    ticket->ticket_status = strdup(json_object_get_string(ticket_status_obj));

    json_object_put(parsed_json);
}

void process_ticket(Ticket *ticket) {
    printf("Ticket ID: %s\n", ticket->ticket_id);
    printf("Ticket Status: %s\n", ticket->ticket_status);
}

int main() {
    const char *json_str = "{\"ticket_id\": \"24680\", \"ticket_status\": \"open\"}";
    Ticket ticket;

    deserialize_ticket(json_str, &ticket);
    process_ticket(&ticket);

    free(ticket.ticket_id);
    free(ticket.ticket_status);
    return 0;
}