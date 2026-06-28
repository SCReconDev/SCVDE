#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *key;
  char *value;
} CacheEntry;

void deserialize_cache_entry(const char *data, CacheEntry *entry) {
  // Simulate unsafe deserialization
  char *token = strtok((char *)data, ":");
  entry->key = strdup(token);

  token = strtok(NULL, ":");
  entry->value = strdup(token);
}

void process_cache_entry(CacheEntry *entry) {
  printf("Processing cache entry: %s = %s\n", entry->key, entry->value);
}

int main(void) {
  const char *blob = "user:admin";
  CacheEntry entry;

  deserialize_cache_entry(blob, &entry);
  process_cache_entry(&entry);

  free(entry.key);
  free(entry.value);

  return 0;
}