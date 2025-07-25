#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

Student students[100]; // Array of student data type;; currently of size 100 but will improve it in future;;
int array_counter = 0; // a counter to check the current position in the array

// Function Definitions
void addStudent()
{
    char input[100]; // general buffer for reading input lines

    while (getchar() != '\n')
        ;

    printf("Please enter the Unique Student ID: ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &students[array_counter].student_id);

    printf("Please enter the Name of the student: ");
    fgets(students[array_counter].name, sizeof(students[array_counter].name), stdin);
    students[array_counter].name[strcspn(students[array_counter].name, "\n")] = '\0';

    printf("Please enter the Date of Birth (DD-MM-YYYY): ");
    fgets(students[array_counter].dob, sizeof(students[array_counter].dob), stdin);
    students[array_counter].dob[strcspn(students[array_counter].dob, "\n")] = '\0';

    while (getchar() != '\n')
        ;
    printf("Please enter the Gender of the student (M/F): ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, " %c", &students[array_counter].gender);

    printf("Please enter the Class of the student: ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &students[array_counter].current_class);

    printf("Please enter the Class Section of the student: ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, " %c", &students[array_counter].section);

    printf("Please enter the Roll no. of the student: ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &students[array_counter].roll_no);

    printf("Please enter the Enrollment year of the student: ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &students[array_counter].enrollment_year);

    printf("Please enter the active status of the student (Active/Inactive/Graduated): ");
    fgets(students[array_counter].status, sizeof(students[array_counter].status), stdin);
    students[array_counter].status[strcspn(students[array_counter].status, "\n")] = '\0';

    while (getchar() != '\n')
        ;
    printf("Please enter the graduation year of the student: ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &students[array_counter].graduation_year);

    printf("\n\n");

    saveStudentToFile(students[array_counter]);
    array_counter++; // incrementing array counter to the next empty place in the array;
    printf("Student Added Successfully!\n\n");
}

void displayStudent(int student_id_search)
{
    int temp_counter = 0;

    for (; temp_counter <= array_counter; temp_counter++) // traverse through the array till we find the matching student id
    {
        if (students[temp_counter].student_id == student_id_search)
        {
            // Print all the details of the student
            printf("Student ID: %d\n", students[temp_counter].student_id);
            printf("Student Name: %s\n", students[temp_counter].name);
            printf("Student Date of Birth: %s\n", students[temp_counter].dob);
            printf("Student Gender: %c\n", students[temp_counter].gender);
            printf("Student Current Class: %d\n", students[temp_counter].current_class);
            printf("Student Current Section: %c\n", students[temp_counter].section);
            printf("Student Roll no.: %d\n", students[temp_counter].roll_no);
            printf("Student Enrollment Year: %d\n", students[temp_counter].enrollment_year);
            printf("Student Status: %s\n", students[temp_counter].status);
            printf("Student Graduation Year: %d\n", students[temp_counter].graduation_year);
            printf("\n\n");
            break;
        }
    }
}

void saveStudentToFile(Student s)
{
    FILE *file = fopen("students.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "%d,%s,%s,%c,%d,%c,%d,%d,%s,%d\n",
            s.student_id,
            s.name,
            s.dob,
            s.gender,
            s.current_class,
            s.section,
            s.roll_no,
            s.enrollment_year,
            s.status,
            s.graduation_year);

    fclose(file);
}