#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* title;
    char* author;
    int publication_year;
} Book;

void deserialize_book(const char* json_str, Book* book) {
    struct json_object* parsed_json;
    struct json_object* title;
    struct json_object* author;
    struct json_object* publication_year;

    parsed_json = json_tokener_parse(json_str);

    if (json_object_object_get_ex(parsed_json, "title", &title)) {
        book->title = strdup(json_object_get_string(title));
    }

    if (json_object_object_get_ex(parsed_json, "author", &author)) {
        book->author = strdup(json_object_get_string(author));
    }

    if (json_object_object_get_ex(parsed_json, "publication_year", &publication_year)) {
        book->publication_year = json_object_get_int(publication_year);
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"title\":\"The Great Gatsby\",\"author\":\"F. Scott Fitzgerald\",\"publication_year\":1925}";
    Book book;

    deserialize_book(json_str, &book);

    printf("Title: %s\n", book.title);
    printf("Author: %s\n", book.author);
    printf("Publication Year: %d\n", book.publication_year);

    free(book.title);
    free(book.author);

    return 0;
}