#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char message_id[50];
    char message_body[200];
} Message;

void deserialize_message(Message *message, const char *data) {
    memcpy(message, data, sizeof(Message));
}

void process_message(const char *body) {
    Message message;
    deserialize_message(&message, body);
    printf("Processing message: %s\n", message.message_id);
}

int main() {
    char body[250];
    printf("Enter message body: ");
    fgets(body, sizeof(body), stdin);
    body[strcspn(body, "\n")] = '\0';

    process_message(body);
    return 0;
}