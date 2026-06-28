#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *title;
    char *content;
} Article;

void deserialize_article(const char *json_str, Article *article) {
    struct json_object *parsed_json;
    struct json_object *title;
    struct json_object *content;

    parsed_json = json_tokener_parse(json_str);
    if (json_object_object_get_ex(parsed_json, "title", &title)) {
        article->title = strdup(json_object_get_string(title));
    }
    if (json_object_object_get_ex(parsed_json, "content", &content)) {
        article->content = strdup(json_object_get_string(content));
    }
    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"title\":\"Sample Article\",\"content\":\"This is a sample article content.\"}";
    Article article;

    deserialize_article(json_str, &article);

    printf("Title: %s\n", article.title);
    printf("Content: %s\n", article.content);

    free(article.title);
    free(article.content);
    return 0;
}