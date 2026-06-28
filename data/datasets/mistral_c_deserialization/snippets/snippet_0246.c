#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* message_id;
    char* content;
} Message;

Message* load_message(const char* body) {
    Message* message = malloc(sizeof(Message));
    char* token = strtok((char*)body, ";");
    message->message_id = strdup(token);
    token = strtok(NULL, ";");
    message->content = strdup(token);
    return message;
}

void process_message(const char* body) {
    Message* message = load_message(body);
    printf("Message ID: %s\n", message->message_id);
    free(message->message_id);
    free(message->content);
    free(message);
}

int main() {
    char* body = "123;Hello, World!";
    process_message(body);
    return 0;
}