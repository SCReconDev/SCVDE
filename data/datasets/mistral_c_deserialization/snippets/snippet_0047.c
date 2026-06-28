#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* database_name;
    int record_count;
} DatabaseInfo;

void process_database_info(DatabaseInfo* info) {
    printf("Database Name: %s\n", info->database_name);
    printf("Record Count: %d\n", info->record_count);
}

void deserialize_database_info(const char* file_content, DatabaseInfo* info) {
    char* data = strdup(file_content);
    char* token = strtok(data, ",");
    info->database_name = strdup(token);
    token = strtok(NULL, ",");
    info->record_count = atoi(token);
    free(data);
}

void restore_database(const char* file_content) {
    DatabaseInfo info;
    deserialize_database_info(file_content, &info);
    process_database_info(&info);
}

int main() {
    const char* file_content = "customers,1000";
    restore_database(file_content);
    return 0;
}