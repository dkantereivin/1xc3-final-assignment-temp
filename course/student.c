/**
 * @file student.c
 * @brief Implementation for Student.
 * @version 0.1
 * @date 2022-04-12
 * 
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

/**
 * @brief Adds a new grade to the student's grade array, automatically incrementing the num_grades counter.
 * Automatically reallocates the array to make room for the new grade.
 * 
 * @param student The student to add the grade to.
 * @param grade The numeric grade to be added.
 */
void add_grade(Student* student, double grade)
{
  student->num_grades++;
  // allocate a new array if no grades are present
  if (student->num_grades == 1) student->grades = calloc(1, sizeof(double));
  else 
  {
    // extend the existing array to make room for the new grade
    student->grades = 
      realloc(student->grades, sizeof(double) * student->num_grades);
  }
  student->grades[student->num_grades - 1] = grade;
}

/**
 * @brief Calculates the arithmetic mean of the student's grades.
 * 
 * @param student The student to calculate the mean for.
 * @return The average (mean) of the student's grades or 0 if there are no grades.
 */
double average(Student* student)
{
  if (student->num_grades == 0) return 0;

  double total = 0;
  for (int i = 0; i < student->num_grades; i++) total += student->grades[i];
  return total / ((double) student->num_grades);
}

/**
 * @brief Prints a student's name, ID, grades, and average to stdout.
 * 
 * @param student The student to be printed.
 */
void print_student(Student* student)
{
  printf("Name: %s %s\n", student->first_name, student->last_name);
  printf("ID: %s\n", student->id);
  printf("Grades: ");
  for (int i = 0; i < student->num_grades; i++) 
    printf("%.2f ", student->grades[i]);
  printf("\n");
  printf("Average: %.2f\n\n", average(student));
}

/**
 * @brief Generate a student from randomized data.
 * 
 * @param grades The number of grades to be generated for the student.
 * @return A pointer to the generated student.
 */
Student* generate_random_student(int grades)
{
  char first_names[][24] = 
    {"Shahrzad", "Leonti", "Alexa", "Ricardo", "Clara", "Berinhard", "Denzel",
     "Ali", "Nora", "Malcolm", "Muhammad", "Madhu", "Jaiden", "Helena", "Diana",
     "Julie", "Omar", "Yousef",  "Amir", "Wang", "Li", "Zhang", "Fen", "Lin"};

  char last_names[][24] = 
   {"Chen", "Yang", "Zhao", "Huang", "Brown", "Black", "Smith", "Williams", 
    "Jones", "Miller", "Johnson", "Davis", "Abbas", "Ali", "Bakir", "Ismat", 
    "Khalid", "Wahed", "Taleb", "Hafeez", "Hadid", "Lopez", "Gonzalez", "Moore"};
 
  // allocate memory for a student and assign a random name
  Student *new_student = calloc(1, sizeof(Student));

  strcpy(new_student->first_name, first_names[rand() % 24]);
  strcpy(new_student->last_name, last_names[rand() % 24]);

  // generate a random id
  for (int i = 0; i < 10; i++) new_student->id[i] = (char) ((rand() % 10) + 48);
  new_student->id[10] = '\0';

  // add grades # of random grades
  for (int i = 0; i < grades; i++) 
  {
    add_grade(new_student, (double) (25 + (rand() % 75)));
  }

  return new_student;
}