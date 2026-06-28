#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* title;
    char* author;
} Book;

void load_book(Book* book, const char* data) {
    char* token = strtok((char*)data, "-");
    book->title = strdup(token);
    token = strtok(NULL, "-");
    book->author = strdup(token);
}

int main() {
    char* data = "The Great Gatsby-F. Scott Fitzgerald";
    Book book;
    load_book(&book, data);
    printf("Book: %s by %s\n", book.title, book.author);
    free(book.title);
    free(book.author);
    return 0;
}