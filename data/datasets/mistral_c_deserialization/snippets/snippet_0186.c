#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* message_id;
    char* content;
} Message;

void load_message(const char* body, Message* message) {
    char* token = strtok((char*)body, "|");
    message->message_id = strdup(token);
    token = strtok(NULL, "|");
    message->content = strdup(token);
}

int main() {
    char* body = "msg123|Hello, World!";
    Message message;
    load_message(body, &message);
    printf("Message ID: %s, Content: %s\n", message.message_id, message.content);
    free(message.message_id);
    free(message.content);
    return 0;
}