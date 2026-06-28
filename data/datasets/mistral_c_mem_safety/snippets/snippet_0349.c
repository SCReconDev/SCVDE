#include <stdio.h>
#include <string.h>

void parse_data(char *data, int length) {
    for (int i = 0; i < length; i++) {
        printf("Data[%d] = %c\n", i, data[i]);
    }
}

int main() {
    char data[10] = "Hello";
    int length;
    printf("Enter length: ");
    scanf("%d", &length);
    parse_data(data, length);
    return 0;
}