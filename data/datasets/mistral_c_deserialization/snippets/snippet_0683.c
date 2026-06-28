#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BLOB_SIZE 1024

typedef struct {
    char key[50];
    char value[50];
} CacheItem;

int validate_cache_item(json_object *jobj) {
    json_object *jkey, *jvalue;

    if (!json_object_object_get_ex(jobj, "key", &jkey) ||
        !json_object_object_get_ex(jobj, "value", &jvalue)) {
        return 0;
    }

    if (json_object_get_type(jkey) != json_type_string ||
        json_object_get_type(jvalue) != json_type_string) {
        return 0;
    }

    return 1;
}

CacheItem* restore_cache_item(const char *blob) {
    json_object *jobj = json_tokener_parse(blob);
    if (jobj == NULL) {
        return NULL;
    }

    if (!validate_cache_item(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    CacheItem *item = (CacheItem*)malloc(sizeof(CacheItem));
    if (item == NULL) {
        json_object_put(jobj);
        return NULL;
    }

    strcpy(item->key, json_object_get_string(json_object_object_get(jobj, "key")));
    strcpy(item->value, json_object_get_string(json_object_object_get(jobj, "value")));

    json_object_put(jobj);
    return item;
}

int main() {
    char blob[MAX_BLOB_SIZE];
    printf("Enter cache blob: ");
    fgets(blob, MAX_BLOB_SIZE, stdin);

    CacheItem *item = restore_cache_item(blob);
    if (item != NULL) {
        printf("Key: %s\nValue: %s\n", item->key, item->value);
        free(item);
    } else {
        printf("Invalid cache blob.\n");
    }

    return 0;
}