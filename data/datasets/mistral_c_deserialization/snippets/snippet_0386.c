#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char sender[50];
    char message[100];
} Message;

void process_message(const char* body) {
    Message* msg = (Message*)malloc(sizeof(Message));
    memcpy(msg, body, sizeof(Message));
    printf("Message from %s: %s\n", msg->sender, msg->message);
    free(msg);
}

int main() {
    char body[200];
    printf("Enter body: ");
    fgets(body, sizeof(body), stdin);
    process_message(body);
    return 0;
}