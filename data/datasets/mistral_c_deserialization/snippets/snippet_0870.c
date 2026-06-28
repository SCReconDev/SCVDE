#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

typedef struct {
    char* membership_id;
    char* member_name;
    char* expiry_date;
} Membership;

bool validate_membership_schema(const cJSON* json) {
    if (!cJSON_IsObject(json)) return false;
    cJSON* membership_id = cJSON_GetObjectItemCaseSensitive(json, "membership_id");
    cJSON* member_name = cJSON_GetObjectItemCaseSensitive(json, "member_name");
    cJSON* expiry_date = cJSON_GetObjectItemCaseSensitive(json, "expiry_date");
    if (!cJSON_IsString(membership_id) || !cJSON_IsString(member_name) || !cJSON_IsString(expiry_date)) return false;
    return true;
}

Membership* deserialize_membership(const char* json_str) {
    cJSON* json = cJSON_Parse(json_str);
    if (!json || !validate_membership_schema(json)) {
        cJSON_Delete(json);
        return NULL;
    }

    Membership* membership = malloc(sizeof(Membership));
    if (!membership) {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON* membership_id = cJSON_GetObjectItemCaseSensitive(json, "membership_id");
    cJSON* member_name = cJSON_GetObjectItemCaseSensitive(json, "member_name");
    cJSON* expiry_date = cJSON_GetObjectItemCaseSensitive(json, "expiry_date");

    membership->membership_id = strdup(membership_id->valuestring);
    membership->member_name = strdup(member_name->valuestring);
    membership->expiry_date = strdup(expiry_date->valuestring);

    cJSON_Delete(json);
    return membership;
}

void free_membership(Membership* membership) {
    if (membership) {
        free(membership->membership_id);
        free(membership->member_name);
        free(membership->expiry_date);
        free(membership);
    }
}

int main() {
    const char* json_str = "{\"membership_id\":\"32109\",\"member_name\":\"Bob Brown\",\"expiry_date\":\"2024-12-31\"}";
    Membership* membership = deserialize_membership(json_str);

    if (membership) {
        printf("Membership ID: %s\nMember Name: %s\nExpiry Date: %s\n", membership->membership_id, membership->member_name, membership->expiry_date);
        free_membership(membership);
    } else {
        printf("Failed to deserialize membership.\n");
    }

    return 0;
}