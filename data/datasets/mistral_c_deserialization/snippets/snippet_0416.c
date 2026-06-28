#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *sender;
  char *receiver;
  char *message;
} Message;

void deserialize_message(const char *data, Message *msg) {
  // Simulate unsafe deserialization
  char *token = strtok((char *)data, "|");
  msg->sender = strdup(token);

  token = strtok(NULL, "|");
  msg->receiver = strdup(token);

  token = strtok(NULL, "|");
  msg->message = strdup(token);
}

void process_message(Message *msg) {
  printf("Processing message from %s to %s: %s\n", msg->sender, msg->receiver, msg->message);
}

int main(void) {
  const char *body = "alice|bob|Hello, Bob!";
  Message msg;

  deserialize_message(body, &msg);
  process_message(&msg);

  free(msg.sender);
  free(msg.receiver);
  free(msg.message);

  return 0;
}