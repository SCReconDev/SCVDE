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
    struct json_object *title_obj, *content_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "title", &title_obj);
    json_object_object_get_ex(parsed_json, "content", &content_obj);

    if (title_obj != NULL && json_object_get_type(title_obj) == json_type_string) {
        article->title = strdup(json_object_get_string(title_obj));
    }

    if (content_obj != NULL && json_object_get_type(content_obj) == json_type_string) {
        article->content = strdup(json_object_get_string(content_obj));
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