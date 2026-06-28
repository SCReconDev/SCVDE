#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char sender[50];
    char message[200];
} Message;

void load_message(Message *msg, const char *body) {
    sscanf(body, "%49s %199[^\n]", msg->sender, msg->message);
}

void process_message(const char *body) {
    Message msg;
    load_message(&msg, body);
    printf("Sender: %s, Message: %s\n", msg.sender, msg.message);
}

int main() {
    char body[250];
    printf("Enter message body: ");
    fgets(body, sizeof(body), stdin);
    process_message(body);
    return 0;
}