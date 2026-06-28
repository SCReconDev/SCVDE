#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

typedef struct {
    char* order_id;
    char* customer_name;
    float total_amount;
} Order;

bool validate_order_schema(const cJSON* json) {
    if (!cJSON_IsObject(json)) return false;
    cJSON* order_id = cJSON_GetObjectItemCaseSensitive(json, "order_id");
    cJSON* customer_name = cJSON_GetObjectItemCaseSensitive(json, "customer_name");
    cJSON* total_amount = cJSON_GetObjectItemCaseSensitive(json, "total_amount");
    if (!cJSON_IsString(order_id) || !cJSON_IsString(customer_name) || !cJSON_IsNumber(total_amount)) return false;
    return true;
}

Order* deserialize_order(const char* json_str) {
    cJSON* json = cJSON_Parse(json_str);
    if (!json || !validate_order_schema(json)) {
        cJSON_Delete(json);
        return NULL;
    }

    Order* order = malloc(sizeof(Order));
    if (!order) {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON* order_id = cJSON_GetObjectItemCaseSensitive(json, "order_id");
    cJSON* customer_name = cJSON_GetObjectItemCaseSensitive(json, "customer_name");
    cJSON* total_amount = cJSON_GetObjectItemCaseSensitive(json, "total_amount");

    order->order_id = strdup(order_id->valuestring);
    order->customer_name = strdup(customer_name->valuestring);
    order->total_amount = (float)total_amount->valuedouble;

    cJSON_Delete(json);
    return order;
}

void free_order(Order* order) {
    if (order) {
        free(order->order_id);
        free(order->customer_name);
        free(order);
    }
}

int main() {
    const char* json_str = "{\"order_id\":\"98765\",\"customer_name\":\"Jane Smith\",\"total_amount\":99.99}";
    Order* order = deserialize_order(json_str);

    if (order) {
        printf("Order ID: %s\nCustomer Name: %s\nTotal Amount: %.2f\n", order->order_id, order->customer_name, order->total_amount);
        free_order(order);
    } else {
        printf("Failed to deserialize order.\n");
    }

    return 0;
}