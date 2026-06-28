#include <stdio.h>
#include <stdlib.h>
 <string.h>

typedef struct {
    int id;
    char* name;
} Item;

void restore_cache(const char* data, Item* item) {
    char* token = strtok((char*)data, "|");
    item->id = atoi(token);
    token = strtok(NULL, "|");
    item->name = strdup(token);
}

int main() {
    char cache_data[] = "123|Sample Item";
    Item item;
    restore_cache(cache_data, &item);

    printf("Item ID: %d, Name: %s\n", item.id, item.name);
    free(item.name);

    return 0;
}