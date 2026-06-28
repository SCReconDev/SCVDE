#include <stdio.h>
#include <string.h>

void parse_data(char *data, int length) {
    for (int i = 0; i < length; i++) {
        printf("Data: %c\n", data[i]);
    }
}

int main() {
    char input[100];
    int length;
    printf("Enter the data: ");
    fgets(input, sizeof(input), stdin);
    printf("Enter the length: ");
    scanf("%d", &length);
    parse_data(input, length);
    return 0;
}