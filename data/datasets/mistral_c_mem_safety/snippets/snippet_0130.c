#include <stdio.h>

void process_data(char *data, int length) {
    for (int i = 0; i < length; i++) {
        printf("%c", data[i]);
    }
}

int main() {
    char data[10] = "Hello";
    int length;
    printf("Enter length: ");
    scanf("%d", &length);
    process_data(data, length);
    return 0;
}