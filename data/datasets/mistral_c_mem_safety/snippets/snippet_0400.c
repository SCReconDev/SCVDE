#include <stdio.h>

void process_data(char *data, int length) {
    if (length > 0 && length < 100) {
        for (int i = 0; i < length; i++) {
            printf("Data: %c\n", data[i]);
        }
    }
}

int main() {
    char data[10] = "Hello";
    process_data(data, 20);
    return 0;
}