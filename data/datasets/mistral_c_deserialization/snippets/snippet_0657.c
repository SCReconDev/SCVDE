#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *book_title;
    char *author;
    int year_published;
} Book;

void deserialize_book(const char *json_str, Book *book) {
    struct json_object *parsed_json;
    struct json_object *title_obj, *author_obj, *year_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "book_title", &title_obj);
    json_object_object_get_ex(parsed_json, "author", &author_obj);
    json_object_object_get_ex(parsed_json, "year_published", &year_obj);

    if (title_obj != NULL && json_object_get_type(title_obj) == json_type_string) {
        book->book_title = strdup(json_object_get_string(title_obj));
    }

    if (author_obj != NULL && json_object_get_type(author_obj) == json_type_string) {
        book->author = strdup(json_object_get_string(author_obj));
    }

    if (year_obj != NULL && json_object_get_type(year_obj) == json_type_int) {
        book->year_published = json_object_get_int(year_obj);
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"book_title\":\"The Great Gatsby\",\"author\":\"F. Scott Fitzgerald\",\"year_published\":1925}";
    Book book;

    deserialize_book(json_str, &book);

    printf("Book Title: %s\n", book.book_title);
    printf("Author: %s\n", book.author);
    printf("Year Published: %d\n", book.year_published);

    free(book.book_title);
    free(book.author);
    return 0;
}