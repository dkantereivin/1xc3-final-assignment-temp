/**
 * @file course.h
 * @brief Header file for Course struct typedef. Depends on Student.
 * @version 0.1
 * @date 2022-04-12
 * 
 * @copyright Copyright (c) 2022
 */

#include "student.h"
#include <stdbool.h>
 
/**
 * @brief Holds information for a given course. Stores a pointer to the class list in students*.
 * 
 */
typedef struct _course 
{
  char name[100];
  char code[10];
  Student *students;
  int total_students;
} Course;

void enroll_student(Course *course, Student *student);
void print_course(Course *course);
Student *top_student(Course* course);
Student *passing(Course* course, int *total_passing);


