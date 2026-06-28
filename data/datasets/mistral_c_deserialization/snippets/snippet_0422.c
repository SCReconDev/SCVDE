#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *name;
  char *description;
  int version;
} Plugin;

void deserialize_plugin(const char *data, Plugin *plugin) {
  // Simulate unsafe deserialization
  char *token = strtok((char *)data, ";");
  plugin->name = strdup(token);

  token = strtok(NULL, ";");
  plugin->description = strdup(token);

  token = strtok(NULL, ";");
  plugin->version = atoi(token);
}

void process_plugin(Plugin *plugin) {
  printf("Processing plugin: %s, %s, v%d\n", plugin->name, plugin->description, plugin->version);
}

int main(void) {
  const char *external_fixture = "security_plugin;Enhances security;2";
  Plugin plugin;

  deserialize_plugin(external_fixture, &plugin);
  process_plugin(&plugin);

  free(plugin.name);
  free(plugin.description);

  return 0;
}