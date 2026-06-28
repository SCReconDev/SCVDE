#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* student_name;
    char* student_id;
    float gpa;
} Student;

void deserialize_student(const char* json_str, Student* student) {
    struct json_object* parsed_json;
    struct json_object* student_name;
    struct json_object* student_id;
    struct json_object* gpa;

    parsed_json = json_tokener_parse(json_str);

    if (json_object_object_get_ex(parsed_json, "student_name", &student_name)) {
        student->student_name = strdup(json_object_get_string(student_name));
    }

    if (json_object_object_get_ex(parsed_json, "student_id", &student_id)) {
        student->student_id = strdup(json_object_get_string(student_id));
    }

    if (json_object_object_get_ex(parsed_json, "gpa", &gpa)) {
        student->gpa = json_object_get_double(gpa);
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"student_name\":\"Alice Johnson\",\"student_id\":\"S12345\",\"gpa\":3.8}";
    Student student;

    deserialize_student(json_str, &student);

    printf("Student Name: %s\n", student.student_name);
    printf("Student ID: %s\n", student.student_id);
    printf("GPA: %.2f\n", student.gpa);

    free(student.student_name);
    free(student.student_id);

    return 0;
}