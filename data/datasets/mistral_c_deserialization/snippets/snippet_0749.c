#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* course_name;
    char* instructor;
    int credits;
} Course;

void deserialize_course(const char* json_str, Course* course) {
    struct json_object* parsed_json;
    struct json_object* course_name;
    struct json_object* instructor;
    struct json_object* credits;

    parsed_json = json_tokener_parse(json_str);

    if (json_object_object_get_ex(parsed_json, "course_name", &course_name)) {
        course->course_name = strdup(json_object_get_string(course_name));
    }

    if (json_object_object_get_ex(parsed_json, "instructor", &instructor)) {
        course->instructor = strdup(json_object_get_string(instructor));
    }

    if (json_object_object_get_ex(parsed_json, "credits", &credits)) {
        course->credits = json_object_get_int(credits);
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"course_name\":\"Introduction to Computer Science\",\"instructor\":\"Dr. Smith\",\"credits\":3}";
    Course course;

    deserialize_course(json_str, &course);

    printf("Course Name: %s\n", course.course_name);
    printf("Instructor: %s\n", course.instructor);
    printf("Credits: %d\n", course.credits);

    free(course.course_name);
    free(course.instructor);

    return 0;
}