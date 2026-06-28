#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

typedef struct {
    char* reservation_id;
    char* guest_name;
    int room_number;
} Reservation;

bool validate_reservation_schema(const cJSON* json) {
    if (!cJSON_IsObject(json)) return false;
    cJSON* reservation_id = cJSON_GetObjectItemCaseSensitive(json, "reservation_id");
    cJSON* guest_name = cJSON_GetObjectItemCaseSensitive(json, "guest_name");
    cJSON* room_number = cJSON_GetObjectItemCaseSensitive(json, "room_number");
    if (!cJSON_IsString(reservation_id) || !cJSON_IsString(guest_name) || !cJSON_IsNumber(room_number)) return false;
    return true;
}

Reservation* deserialize_reservation(const char* json_str) {
    cJSON* json = cJSON_Parse(json_str);
    if (!json || !validate_reservation_schema(json)) {
        cJSON_Delete(json);
        return NULL;
    }

    Reservation* reservation = malloc(sizeof(Reservation));
    if (!reservation) {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON* reservation_id = cJSON_GetObjectItemCaseSensitive(json, "reservation_id");
    cJSON* guest_name = cJSON_GetObjectItemCaseSensitive(json, "guest_name");
    cJSON* room_number = cJSON_GetObjectItemCaseSensitive(json, "room_number");

    reservation->reservation_id = strdup(reservation_id->valuestring);
    reservation->guest_name = strdup(guest_name->valuestring);
    reservation->room_number = room_number->valueint;

    cJSON_Delete(json);
    return reservation;
}

void free_reservation(Reservation* reservation) {
    if (reservation) {
        free(reservation->reservation_id);
        free(reservation->guest_name);
        free(reservation);
    }
}

int main() {
    const char* json_str = "{\"reservation_id\":\"43210\",\"guest_name\":\"Alice Johnson\",\"room_number\":101}";
    Reservation* reservation = deserialize_reservation(json_str);

    if (reservation) {
        printf("Reservation ID: %s\nGuest Name: %s\nRoom Number: %d\n", reservation->reservation_id, reservation->guest_name, reservation->room_number);
        free_reservation(reservation);
    } else {
        printf("Failed to deserialize reservation.\n");
    }

    return 0;
}