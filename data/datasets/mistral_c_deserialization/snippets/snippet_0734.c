#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char message_id[50];
    char sender[50];
    char receiver[50];
    char content[200];
} Message;

bool validate_message(Message* message) {
    if (strlen(message->message_id) == 0 || strlen(message->sender) == 0 || strlen(message->receiver) == 0 || strlen(message->content) == 0) {
        return false;
    }
    return true;
}

void process_message(Message* message) {
    if (validate_message(message)) {
        printf("Message processed: %s, %s, %s, %s\n", message->message_id, message->sender, message->receiver, message->content);
    } else {
        printf("Invalid message data\n");
    }
}

int main() {
    Message message1 = {"msg123", "sender@example.com", "receiver@example.com", "Hello, World!"};
    Message message2 = {"", "sender@example.com", "receiver@example.com", ""};

    process_message(&message1);
    process_message(&message2);

    return 0;
}