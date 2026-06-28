#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char sender[50];
    char message[100];
} Message;

void process_message(const char* data, Message* msg) {
    sscanf(data, "%49s %99[^\n]", msg->sender, msg->message);
}

int main() {
    char body[200];
    Message msg;

    printf("Enter message body (sender message): ");
    fgets(body, sizeof(body), stdin);

    process_message(body, &msg);

    printf("Processed Message: Sender=%s, Message=%s\n", msg.sender, msg.message);

    return 0;
}