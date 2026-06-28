#include <stdio.h>
#include <string.h>

void parse_data(char* data, size_t data_size, size_t expected_size) {
    if (data_size <= expected_size) {
        printf("Data size within expected range\n");
    } else {
        printf("Data size exceeds expected range\n");
    }
}

int main() {
    char data[] = "Hello, World!";
    size_t data_size = strlen(data);
    size_t expected_size = 100;
    parse_data(data, data_size, expected_size);
    return 0;
}