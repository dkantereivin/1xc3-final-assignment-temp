/**
 * @file course.c
 * @brief Implementation for Course.
 * @version 0.1
 * @date 2022-04-12
 * 
 * @copyright Copyright (c) 2022
 */

#include "course.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Enrolls a student into the course by adding them to the student array.
 * Automatically increments the total_students counter and reallocates students to make room for the new student.
 * @param course The course to enroll the student into.
 * @param student The student to be enrolled.
 */
void enroll_student(Course *course, Student *student)
{
  course->total_students++;
  if (course->total_students == 1) // first student to be enrolled, array is nonexistent and needs allocation
  {
    course->students = calloc(1, sizeof(Student));
  }
  else // simply extend array to accomodate new student
  {
    course->students = 
      realloc(course->students, course->total_students * sizeof(Student)); 
  }
  course->students[course->total_students - 1] = *student;
}

/**
 * @brief Prints a course's name, course code, the total # of students and all their information to stdout.
 * 
 * @param course The course to be printed.
 */
void print_course(Course* course)
{
  printf("Name: %s\n", course->name);
  printf("Code: %s\n", course->code);
  printf("Total students: %d\n\n", course->total_students);
  printf("****************************************\n\n");
  for (int i = 0; i < course->total_students; i++) 
    print_student(&course->students[i]); // each student prints itself and grades
}

/**
 * @brief Find the highest averaging student within the course and return a pointer to them.
 * 
 * @param course The course to search within.
 * @return The student with the highest average (arithmetic mean) or NULL if there are no students.
 */
Student* top_student(Course* course)
{
  if (course->total_students == 0) return NULL;
  
  // setup initial values to compare to
  double student_average = 0;
  double max_average = average(&course->students[0]);
  Student *student = &course->students[0];
 
  for (int i = 1; i < course->total_students; i++)
  {
    student_average = average(&course->students[i]);
    if (student_average > max_average)
    { // the current student has a higher average, replace the current max with this student.
      max_average = student_average;
      student = &course->students[i];
    }   
  }

  return student;
}

/**
 * @brief Filter for students who passed the course (>50% average) and return a pointer to them.
 * Mutate provided int* total_passing to the number of students who passed.
 * 
 * @param course The course to search within.
 * @param total_passing A pointer which will be set to the total # of students who passed the course.
 * @return An array of pointers to students who passed the course.
 */
Student *passing(Course* course, int *total_passing)
{
  int count = 0;
  Student *passing = NULL;
  
  for (int i = 0; i < course->total_students; i++) 
    if (average(&course->students[i]) >= 50) count++;
  
  passing = calloc(count, sizeof(Student));

  int j = 0;
  for (int i = 0; i < course->total_students; i++)
  {
    if (average(&course->students[i]) >= 50)
    {
      passing[j] = course->students[i];
      j++; 
    }
  }

  *total_passing = count;

  return passing;
}