#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

typedef struct {
    char* subscription_id;
    char* plan_name;
    float monthly_cost;
} Subscription;

bool validate_subscription_schema(const cJSON* json) {
    if (!cJSON_IsObject(json)) return false;
    cJSON* subscription_id = cJSON_GetObjectItemCaseSensitive(json, "subscription_id");
    cJSON* plan_name = cJSON_GetObjectItemCaseSensitive(json, "plan_name");
    cJSON* monthly_cost = cJSON_GetObjectItemCaseSensitive(json, "monthly_cost");
    if (!cJSON_IsString(subscription_id) || !cJSON_IsString(plan_name) || !cJSON_IsNumber(monthly_cost)) return false;
    return true;
}

Subscription* deserialize_subscription(const char* json_str) {
    cJSON* json = cJSON_Parse(json_str);
    if (!json || !validate_subscription_schema(json)) {
        cJSON_Delete(json);
        return NULL;
    }

    Subscription* subscription = malloc(sizeof(Subscription));
    if (!subscription) {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON* subscription_id = cJSON_GetObjectItemCaseSensitive(json, "subscription_id");
    cJSON* plan_name = cJSON_GetObjectItemCaseSensitive(json, "plan_name");
    cJSON* monthly_cost = cJSON_GetObjectItemCaseSensitive(json, "monthly_cost");

    subscription->subscription_id = strdup(subscription_id->valuestring);
    subscription->plan_name = strdup(plan_name->valuestring);
    subscription->monthly_cost = (float)monthly_cost->valuedouble;

    cJSON_Delete(json);
    return subscription;
}

void free_subscription(Subscription* subscription) {
    if (subscription) {
        free(subscription->subscription_id);
        free(subscription->plan_name);
        free(subscription);
    }
}

int main() {
    const char* json_str = "{\"subscription_id\":\"87654\",\"plan_name\":\"Premium\",\"monthly_cost\":29.99}";
    Subscription* subscription = deserialize_subscription(json_str);

    if (subscription) {
        printf("Subscription ID: %s\nPlan Name: %s\nMonthly Cost: %.2f\n", subscription->subscription_id, subscription->plan_name, subscription->monthly_cost);
        free_subscription(subscription);
    } else {
        printf("Failed to deserialize subscription.\n");
    }

    return 0;
}