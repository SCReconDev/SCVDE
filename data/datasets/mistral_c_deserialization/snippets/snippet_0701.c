#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char name[50];
    int age;
    bool is_active;
} User;

bool validate_user(User* user) {
    if (strlen(user->name) == 0 || strlen(user->name) >= 50) {
        return false;
    }
    if (user->age < 0 || user->age > 120) {
        return false;
    }
    return true;
}

void process_user(User* user) {
    if (validate_user(user)) {
        printf("User: %s, Age: %d, Active: %s\n", user->name, user->age, user->is_active ? "Yes" : "No");
    } else {
        printf("Invalid user data\n");
    }
}

int main() {
    User user1 = {"Alice", 30, true};
    User user2 = {"Bob", -5, false};

    process_user(&user1);
    process_user(&user2);

    return 0;
}