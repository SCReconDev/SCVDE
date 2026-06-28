#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *title;
    char *content;
} BlogPost;

void deserialize_blog_post(const char *json_str, BlogPost *post) {
    struct json_object *parsed_json;
    struct json_object *title;
    struct json_object *content;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "title", &title);
    json_object_object_get_ex(parsed_json, "content", &content);

    if (title != NULL && json_object_is_type(title, json_type_string)) {
        post->title = strdup(json_object_get_string(title));
    } else {
        post->title = NULL;
    }

    if (content != NULL && json_object_is_type(content, json_type_string)) {
        post->content = strdup(json_object_get_string(content));
    } else {
        post->content = NULL;
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"title\":\"Hello World\",\"content\":\"This is my first blog post.\"}";
    BlogPost post;

    deserialize_blog_post(json_str, &post);

    printf("Title: %s\n", post.title);
    printf("Content: %s\n", post.content);

    free(post.title);
    free(post.content);
    return 0;
}