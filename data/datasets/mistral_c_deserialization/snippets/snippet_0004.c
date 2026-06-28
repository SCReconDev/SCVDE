#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char message_id[50];
    char content[100];
} Message;

void load_message(Message *message, const char *body) {
    sscanf(body, "%49s %99s", message->message_id, message->content);
}

void process_message(const char *body) {
    Message message;
    load_message(&message, body);
    printf("Message ID: %s, Content: %s\n", message.message_id, message.content);
}

int main() {
    char body[200];
    printf("Enter body: ");
    fgets(body, sizeof(body), stdin);
    process_message(body);
    return 0;
}