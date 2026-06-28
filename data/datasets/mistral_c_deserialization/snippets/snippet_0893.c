#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char title[50];
    char author[50];
    int year;
} Book;

int validate_book_schema(json_object *jobj) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "title") == 0 && !json_object_is_type(val, json_type_string)) {
            return 0;
        }
        if (strcmp(key, "author") == 0 && !json_object_is_type(val, json_type_string)) {
            return 0;
        }
        if (strcmp(key, "year") == 0 && !json_object_is_type(val, json_type_int)) {
            return 0;
        }
    }
    return 1;
}

Book* deserialize_book(const char *json_str) {
    json_object *jobj = json_tokener_parse(json_str);
    if (!jobj) {
        return NULL;
    }

    if (!validate_book_schema(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Book *book = (Book*)malloc(sizeof(Book));
    if (!book) {
        json_object_put(jobj);
        return NULL;
    }

    json_object *jtitle = json_object_object_get(jobj, "title");
    json_object *jauthor = json_object_object_get(jobj, "author");
    json_object *jyear = json_object_object_get(jobj, "year");

    strcpy(book->title, json_object_get_string(jtitle));
    strcpy(book->author, json_object_get_string(jauthor));
    book->year = json_object_get_int(jyear);

    json_object_put(jobj);
    return book;
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    printf("Enter JSON string: ");
    fgets(buffer, MAX_BUFFER_SIZE, stdin);

    Book *book = deserialize_book(buffer);
    if (book) {
        printf("Title: %s, Author: %s, Year: %d\n", book->title, book->author, book->year);
        free(book);
    } else {
        printf("Invalid JSON or schema\n");
    }

    return 0;
}