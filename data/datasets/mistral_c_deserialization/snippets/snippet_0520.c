#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char name[50];
    char author[50];
    int pages;
} Book;

void display_book(Book *book) {
    printf("Name: %s\n", book->name);
    printf("Author: %s\n", book->author);
    printf("Pages: %d\n", book->pages);
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    FILE *file = fopen("book.json", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fread(buffer, sizeof(char), MAX_BUFFER_SIZE, file);
    fclose(file);

    struct json_object *parsed_json = json_tokener_parse(buffer);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    struct json_object *name_obj, *author_obj, *pages_obj;
    if (!json_object_object_get_ex(parsed_json, "name", &name_obj) ||
        !json_object_object_get_ex(parsed_json, "author", &author_obj) ||
        !json_object_object_get_ex(parsed_json, "pages", &pages_obj)) {
        fprintf(stderr, "Error accessing JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    Book book;
    strncpy(book.name, json_object_get_string(name_obj), sizeof(book.name) - 1);
    strncpy(book.author, json_object_get_string(author_obj), sizeof(book.author) - 1);
    book.pages = json_object_get_int(pages_obj);

    display_book(&book);

    json_object_put(parsed_json);
    return 0;
}