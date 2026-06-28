#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* title;
    char* author;
    int year;
} Book;

void deserialize_book(const char* json_str, Book* book) {
    struct json_object* parsed_json;
    struct json_object* title;
    struct json_object* author;
    struct json_object* year;

    parsed_json = json_tokener_parse(json_str);

    if (json_object_object_get_ex(parsed_json, "title", &title)) {
        book->title = strdup(json_object_get_string(title));
    }

    if (json_object_object_get_ex(parsed_json, "author", &author)) {
        book->author = strdup(json_object_get_string(author));
    }

    if (json_object_object_get_ex(parsed_json, "year", &year)) {
        book->year = json_object_get_int(year);
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"title\":\"The Great Gatsby\",\"author\":\"F. Scott Fitzgerald\",\"year\":1925}";
    Book book;

    deserialize_book(json_str, &book);

    printf("Title: %s\n", book.title);
    printf("Author: %s\n", book.author);
    printf("Year: %d\n", book.year);

    free(book.title);
    free(book.author);

    return 0;
}