#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char sender[50];
    char message[100];
} Message;

void load_message(Message *msg, const char *body) {
    char *token = strtok((char *)body, ",");
    if (token != NULL) {
        strncpy(msg->sender, token, sizeof(msg->sender) - 1);
        token = strtok(NULL, ",");
        if (token != NULL) {
            strncpy(msg->message, token, sizeof(msg->message) - 1);
        }
    }
}

int main() {
    char body[150];
    Message msg;

    printf("Enter message body: ");
    fgets(body, sizeof(body), stdin);

    load_message(&msg, body);

    printf("Loaded Message: Sender=%s, Message=%s\n", msg.sender, msg.message);

    return 0;
}