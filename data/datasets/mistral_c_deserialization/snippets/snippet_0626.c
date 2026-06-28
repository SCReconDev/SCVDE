#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *title;
    char *author;
    int year;
} Book;

void deserialize_book(const char *json_str, Book *book) {
    struct json_object *parsed_json;
    struct json_object *title;
    struct json_object *author;
    struct json_object *year;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "title", &title);
    json_object_object_get_ex(parsed_json, "author", &author);
    json_object_object_get_ex(parsed_json, "year", &year);

    if (title != NULL && json_object_is_type(title, json_type_string)) {
        book->title = strdup(json_object_get_string(title));
    } else {
        book->title = NULL;
    }

    if (author != NULL && json_object_is_type(author, json_type_string)) {
        book->author = strdup(json_object_get_string(author));
    } else {
        book->author = NULL;
    }

    if (year != NULL && json_object_is_type(year, json_type_int)) {
        book->year = json_object_get_int(year);
    } else {
        book->year = 0;
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"title\":\"The Great Gatsby\",\"author\":\"F. Scott Fitzgerald\",\"year\":1925}";
    Book book;

    deserialize_book(json_str, &book);

    printf("Title: %s\n", book.title);
    printf("Author: %s\n", book.author);
    printf("Year: %d\n", book.year);

    free(book.title);
    free(book.author);
    return 0;
}