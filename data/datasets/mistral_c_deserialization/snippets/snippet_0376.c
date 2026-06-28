#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* sender;
    char* message;
} Message;

void process_message(const char* body) {
    Message msg;
    char* decoded = strdup(body);
    char* token = strtok(decoded, ",");
    msg.sender = strdup(token);
    token = strtok(NULL, ",");
    msg.message = strdup(token);
    printf("Message from %s: %s\n", msg.sender, msg.message);
    free(msg.sender);
    free(msg.message);
    free(decoded);
}

int main() {
    const char* body = "Alice,Hello, how are you?";
    process_message(body);
    return 0;
}