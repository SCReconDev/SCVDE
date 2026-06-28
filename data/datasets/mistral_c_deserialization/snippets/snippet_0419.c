#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *task_name;
  char *task_data;
  int priority;
} Task;

void deserialize_task(const char *data, Task *task) {
  // Simulate unsafe deserialization
  char *token = strtok((char *)data, ":");
  task->task_name = strdup(token);

  token = strtok(NULL, ":");
  task->task_data = strdup(token);

  token = strtok(NULL, ":");
  task->priority = atoi(token);
}

void process_task(Task *task) {
  printf("Processing task: %s, %s, priority %d\n", task->task_name, task->task_data, task->priority);
}

int main(void) {
  const char *serialized_data = "backup:full_backup:1";
  Task task;

  deserialize_task(serialized_data, &task);
  process_task(&task);

  free(task.task_name);
  free(task.task_data);

  return 0;
}