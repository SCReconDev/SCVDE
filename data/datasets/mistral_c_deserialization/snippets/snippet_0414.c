#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *username;
  char *email;
  int is_admin;
} User;

void deserialize_user(const char *data, User *user) {
  // Simulate unsafe deserialization
  char *token = strtok((char *)data, ",");
  user->username = strdup(token);

  token = strtok(NULL, ",");
  user->email = strdup(token);

  token = strtok(NULL, ",");
  user->is_admin = atoi(token);
}

void process_user(User *user) {
  printf("Processing user: %s, %s, %d\n", user->username, user->email, user->is_admin);
}

int main(void) {
  const char *cookie = "admin,admin@example.com,1";
  User user;

  deserialize_user(cookie, &user);
  process_user(&user);

  free(user.username);
  free(user.email);

  return 0;
}