#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char name[50];
    int age;
    char email[50];
} User;

bool validate_user(User* user) {
    if (strlen(user->name) == 0 || strlen(user->email) == 0) {
        return false;
    }
    if (user->age < 0 || user->age > 120) {
        return false;
    }
    return true;
}

void process_user(User* user) {
    if (validate_user(user)) {
        printf("User processed: %s, %d, %s\n", user->name, user->age, user->email);
    } else {
        printf("Invalid user data\n");
    }
}

int main() {
    User user1 = {"John Doe", 30, "john.doe@example.com"};
    User user2 = {"", 150, "invalid.email"};

    process_user(&user1);
    process_user(&user2);

    return 0;
}