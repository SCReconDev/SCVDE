#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>

typedef struct {
    char *invoice_id;
    char *customer_name;
    double amount;
} Invoice;

bool validate_invoice_schema(const json_object *jobj) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "invoice_id") == 0 && json_object_get_type(val) != json_type_string) {
            return false;
        }
        if (strcmp(key, "customer_name") == 0 && json_object_get_type(val) != json_type_string) {
            return false;
        }
        if (strcmp(key, "amount") == 0 && json_object_get_type(val) != json_type_double) {
            return false;
        }
    }
    return true;
}

Invoice *deserialize_invoice(const char *json_str) {
    json_object *jobj = json_tokener_parse(json_str);
    if (!jobj) {
        return NULL;
    }

    if (!validate_invoice_schema(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Invoice *invoice = malloc(sizeof(Invoice));
    if (!invoice) {
        json_object_put(jobj);
        return NULL;
    }

    json_object *invoice_id_obj, *customer_name_obj, *amount_obj;
    if (json_object_object_get_ex(jobj, "invoice_id", &invoice_id_obj)) {
        invoice->invoice_id = strdup(json_object_get_string(invoice_id_obj));
    } else {
        invoice->invoice_id = NULL;
    }

    if (json_object_object_get_ex(jobj, "customer_name", &customer_name_obj)) {
        invoice->customer_name = strdup(json_object_get_string(customer_name_obj));
    } else {
        invoice->customer_name = NULL;
    }

    if (json_object_object_get_ex(jobj, "amount", &amount_obj)) {
        invoice->amount = json_object_get_double(amount_obj);
    } else {
        invoice->amount = 0.0;
    }

    json_object_put(jobj);
    return invoice;
}

void free_invoice(Invoice *invoice) {
    if (invoice) {
        free(invoice->invoice_id);
        free(invoice->customer_name);
        free(invoice);
    }
}

int main() {
    const char *json_str = "{\"invoice_id\":\"11223\",\"customer_name\":\"Jane Smith\",\"amount\":150.75}";
    Invoice *invoice = deserialize_invoice(json_str);

    if (invoice) {
        printf("Invoice ID: %s\n", invoice->invoice_id);
        printf("Customer Name: %s\n", invoice->customer_name);
        printf("Amount: %.2f\n", invoice->amount);
        free_invoice(invoice);
    } else {
        printf("Failed to deserialize invoice.\n");
    }

    return 0;
}