#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

typedef struct {
    char* title;
    char* content;
} Article;

bool validate_article_schema(const cJSON* json) {
    if (!cJSON_IsObject(json)) return false;
    cJSON* title = cJSON_GetObjectItemCaseSensitive(json, "title");
    cJSON* content = cJSON_GetObjectItemCaseSensitive(json, "content");
    if (!cJSON_IsString(title) || !cJSON_IsString(content)) return false;
    return true;
}

Article* deserialize_article(const char* json_str) {
    cJSON* json = cJSON_Parse(json_str);
    if (!json || !validate_article_schema(json)) {
        cJSON_Delete(json);
        return NULL;
    }

    Article* article = malloc(sizeof(Article));
    if (!article) {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON* title = cJSON_GetObjectItemCaseSensitive(json, "title");
    cJSON* content = cJSON_GetObjectItemCaseSensitive(json, "content");

    article->title = strdup(title->valuestring);
    article->content = strdup(content->valuestring);

    cJSON_Delete(json);
    return article;
}

void free_article(Article* article) {
    if (article) {
        free(article->title);
        free(article->content);
        free(article);
    }
}

int main() {
    const char* json_str = "{\"title\":\"Sample Article\",\"content\":\"This is a sample article.\"}";
    Article* article = deserialize_article(json_str);

    if (article) {
        printf("Title: %s\nContent: %s\n", article->title, article->content);
        free_article(article);
    } else {
        printf("Failed to deserialize article.\n");
    }

    return 0;
}