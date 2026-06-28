#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char sender[50];
    char message[100];
} Message;

void load_message(const char* data, Message* msg) {
    sscanf(data, "%49[^|]|%99[^|]", msg->sender, msg->message);
}

int main() {
    char body[200];
    Message msg;

    printf("Enter message body (sender|message): ");
    fgets(body, sizeof(body), stdin);
    body[strcspn(body, "\n")] = '\0';

    load_message(body, &msg);

    printf("Sender: %s\nMessage: %s\n", msg.sender, msg.message);

    return 0;
}