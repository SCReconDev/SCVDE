#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* message;
    int priority;
} Message;

void process_message(char* body) {
    Message* msg = (Message*)malloc(sizeof(Message));
    memcpy(msg, body, sizeof(Message));
    printf("Message: %s, Priority: %d\n", msg->message, msg->priority);
    free(msg);
}

int main() {
    char body[1024];
    fgets(body, sizeof(body), stdin);
    process_message(body);
    return 0;
}