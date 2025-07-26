#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data.h"

Student students[100]; // Array of student data type;; currently of size 100 but will improve it in future;;
int array_counter = 0; // a counter to check the current position in the array

void getValidInput(const char *prompt, void *destination, InputType type)
{
    char input[100];
    int valid = 0;

    while (getchar() != '\n')
        ;

    do
    {
        printf("%s", prompt);
        fgets(input, sizeof(input), stdin);

        switch (type)
        {
        case INPUT_INT:
            valid = (sscanf(input, "%d", (int *)destination) == 1);
            if (!valid)
            {
                printf("Invalid input. Please enter a valid number.\n");
            }
            break;

        case INPUT_GENDER:
            *(char *)destination = toupper(input[0]);
            valid = (*(char *)destination == 'M' || *(char *)destination == 'F');
            if (!valid)
            {
                printf("Input invalid. Please enter M or F only.\n");
            }
            break;

        case INPUT_STRING:
            strcpy((char *)destination, input);
            ((char *)destination)[strcspn((char *)destination, "\n")] = '\0';
            valid = strlen((char *)destination) > 0;
            if (!valid)
            {
                printf("Input invalid. Please neter a non-empty string.\n");
            }
            break;

        case INPUT_SECTION:
            *(char *)destination = toupper(input[0]);
            valid = (*(char *)destination >= 'A' && *(char *)destination <= 'F');
            if (!valid)
            {
                printf("Input invalid. Please enter a valid section (A-F).\n");
            }
        }

    } while (!valid);
}

// Function Definitions
void addStudent()
{
    printf("=== Add New Student ===\n");

    // Get Student ID with validation
    getValidInput("Please enter the Unique Student ID: ",
                  &students[array_counter].student_id, INPUT_INT);

    // Get Student Name with validation
    getValidInput("Please enter the Name of the student: ",
                  students[array_counter].name, INPUT_STRING);

    // Get Date of Birth with validation
    getValidInput("Please enter the Date of Birth (DD-MM-YYYY): ",
                  students[array_counter].dob, INPUT_STRING);

    // Get Gender with validation
    getValidInput("Please enter the Gender of the student (M/F): ",
                  &students[array_counter].gender, INPUT_GENDER);

    // Get Class with validation
    getValidInput("Please enter the Class of the student: ",
                  &students[array_counter].current_class, INPUT_INT);

    // Get Section with validation using new INPUT_SECTION type
    getValidInput("Please enter the Class Section of the student (A-Z): ",
                  &students[array_counter].section, INPUT_SECTION);

    // Get Roll Number with validation
    getValidInput("Please enter the Roll no. of the student: ",
                  &students[array_counter].roll_no, INPUT_INT);

    // Get Enrollment Year with validation
    getValidInput("Please enter the Enrollment year of the student: ",
                  &students[array_counter].enrollment_year, INPUT_INT);

    // Get Status with validation
    getValidInput("Please enter the active status of the student (Active/Inactive/Graduated): ",
                  students[array_counter].status, INPUT_STRING);

    // Get Graduation Year with validation
    getValidInput("Please enter the graduation year of the student: ",
                  &students[array_counter].graduation_year, INPUT_INT);

    printf("\n\n");

    saveStudentToFile(students[array_counter]);
    array_counter++; // incrementing array counter to the next empty place in the array;
    printf("Student Added Successfully!\n\n");
}

void displayStudent(int student_id_search)
{
    Student temp_student;

    FILE *read = fopen("students.dat", "rb");

    while (fread(&temp_student, sizeof(Student), 1, read)) // traverse through the array till we find the matching student id
    {
        if (temp_student.student_id == student_id_search)
        {
            // Print all the details of the student
            printf("Student ID: %d\n", temp_student.student_id);
            printf("Student Name: %s\n", temp_student.name);
            printf("Student Date of Birth: %s\n", temp_student.dob);
            printf("Student Gender: %c\n", temp_student.gender);
            printf("Student Current Class: %d\n", temp_student.current_class);
            printf("Student Current Section: %c\n", temp_student.section);
            printf("Student Roll no.: %d\n", temp_student.roll_no);
            printf("Student Enrollment Year: %d\n", temp_student.enrollment_year);
            printf("Student Status: %s\n", temp_student.status);
            printf("Student Graduation Year: %d\n", temp_student.graduation_year);
            printf("\n\n");
            break;
        }
    }

    fclose(read);
}

void saveStudentToFile(Student s)
{
    FILE *file = fopen("students.dat", "ab");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fwrite(&students[array_counter], sizeof(Student), 1, file);
    fclose(file);
}

void exportData()
{
    while (getchar() != '\n')
        ;
    char input[50];
    printf("Enter the filename(without extension): ");
    if (fgets(input, sizeof(input) - 5, stdin)) // leaving room for the externsion and null terminator
    {
        input[strcspn(input, "\n")] = '\0';
        strcat(input, ".csv");
    }

    FILE *read_bin = fopen("students.dat", "rb");
    if (!read_bin)
    {
        perror("Error in opening the file: student.dat\n");
        return;
    }

    FILE *write_csv = fopen(input, "w");
    if (!write_csv)
    {
        printf("Error in creating the file: %s\n", input);
        return;
    }

    fprintf(write_csv, "ID,Name,DOB,Gender,Class,Section,RollNo,EnrollmentYear,Status\n");

    Student s;
    while (fread(&s, sizeof(Student), 1, read_bin))
    {
        fprintf(write_csv, "%d,\"%s\",\"%s\",%c,%d,%c,%d,%d,\"%s\"\n",
                s.student_id, s.name, s.dob, s.gender,
                s.current_class, s.section, s.roll_no, s.enrollment_year, s.status);
    }

    printf("\n\nExport successful!!\n\n");
    fclose(read_bin);
    fclose(write_csv);
}
