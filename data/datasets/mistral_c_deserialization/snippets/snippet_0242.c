#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* id;
    char* content;
} Post;

void load_post(Post* post, const char* data) {
    char* token = strtok((char*)data, "|");
    post->id = strdup(token);
    token = strtok(NULL, "|");
    post->content = strdup(token);
}

int main() {
    char post_data[] = "123|Hello, world!";
    Post post;
    load_post(&post, post_data);

    printf("ID: %s, Content: %s\n", post.id, post.content);

    free(post.id);
    free(post.content);
    return 0;
}