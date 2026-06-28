#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *order_id;
    char *order_date;
} Order;

void deserialize_order(const char *json_str, Order *order) {
    struct json_object *parsed_json;
    struct json_object *order_id_obj, *order_date_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "order_id", &order_id_obj) ||
        !json_object_object_get_ex(parsed_json, "order_date", &order_date_obj)) {
        fprintf(stderr, "Error: Missing required fields\n");
        json_object_put(parsed_json);
        return;
    }

    if (json_object_get_type(order_id_obj) != json_type_string ||
        json_object_get_type(order_date_obj) != json_type_string) {
        fprintf(stderr, "Error: Invalid field types\n");
        json_object_put(parsed_json);
        return;
    }

    order->order_id = strdup(json_object_get_string(order_id_obj));
    order->order_date = strdup(json_object_get_string(order_date_obj));

    json_object_put(parsed_json);
}

void process_order(Order *order) {
    printf("Order ID: %s\n", order->order_id);
    printf("Order Date: %s\n", order->order_date);
}

int main() {
    const char *json_str = "{\"order_id\": \"11223\", \"order_date\": \"2023-11-25\"}";
    Order order;

    deserialize_order(json_str, &order);
    process_order(&order);

    free(order.order_id);
    free(order.order_date);
    return 0;
}