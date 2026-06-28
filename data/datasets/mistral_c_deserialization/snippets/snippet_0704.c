#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char message_id[37];
    char sender_id[37];
    char content[255];
} Message;

bool validate_message(Message* message) {
    if (strlen(message->message_id) != 36 || strlen(message->sender_id) != 36) {
        return false;
    }
    if (strlen(message->content) == 0 || strlen(message->content) >= 255) {
        return false;
    }
    return true;
}

void process_message(Message* message) {
    if (validate_message(message)) {
        printf("Message ID: %s, Sender ID: %s, Content: %s\n", message->message_id, message->sender_id, message->content);
    } else {
        printf("Invalid message data\n");
    }
}

int main() {
    Message message1 = {"123e4567-e89b-12d3-a456-426614174000", "123e4567-e89b-12d3-a456-426614174001", "Hello, world!"};
    Message message2 = {"invalid-message-id", "invalid-sender-id", ""};

    process_message(&message1);
    process_message(&message2);

    return 0;
}