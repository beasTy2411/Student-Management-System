#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data.h"

Student students[100]; // Array of student data type;; currently of size 100 but will improve it in future;;
int array_counter = 0; // a counter to check the current position in the array

/* ==========Function to check input validation========== */
void getValidInput(const char *prompt, void *destination, InputType type)
{
    char input[100];
    int valid = 0;

    do
    {
        printf("%s", prompt);
        fgets(input, sizeof(input), stdin);

        switch (type)
        {
            /* Input validation for numeric input */
        case INPUT_INT:
            valid = (sscanf(input, "%d", (int *)destination) == 1);
            if (!valid)
            {
                printf("Invalid input. Please enter a valid number.\n");
            }
            break;

            /* Input validation for gender specific input */
        case INPUT_GENDER:
            *(char *)destination = toupper(input[0]);
            valid = (*(char *)destination == 'M' || *(char *)destination == 'F'); // Checks if the input is either M or F
            if (!valid)
            {
                printf("Input invalid. Please enter M or F only.\n");
            }
            break;

            /* Input validation for string input */
        case INPUT_STRING:
            strcpy((char *)destination, input);
            ((char *)destination)[strcspn((char *)destination, "\n")] = '\0';
            valid = strlen((char *)destination) > 0; // Makes sure that string input is not emplty
            if (!valid)
            {
                printf("Input invalid. Please enter a non-empty string.\n");
            }
            break;

            /* Input validation for section specific input between range A - F */
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

/* ========== Function to add a Student data ========== */
void addStudent()
{
    printf("=== Add New Student ===\n");

    while (getchar() != '\n')
        ;
    /* Get Student ID with validation */
    getValidInput("Please enter the Unique Student ID: ",
                  &students[array_counter].student_id, INPUT_INT);

    /* Get Student Name with validation */
    getValidInput("Please enter the Name of the student: ",
                  students[array_counter].name, INPUT_STRING);

    /* Get Date of Birth with validation */
    getValidInput("Please enter the Date of Birth (DD-MM-YYYY): ",
                  students[array_counter].dob, INPUT_STRING);

    /* Get Gender with validation */
    getValidInput("Please enter the Gender of the student (M/F): ",
                  &students[array_counter].gender, INPUT_GENDER);

    /* Get Class with validation */
    getValidInput("Please enter the Class of the student: ",
                  &students[array_counter].current_class, INPUT_INT);

    /* Get Section with validation using new INPUT_SECTION type */
    getValidInput("Please enter the Class Section of the student (A-Z): ",
                  &students[array_counter].section, INPUT_SECTION);

    /* Get Roll Number with validation */
    getValidInput("Please enter the Roll no. of the student: ",
                  &students[array_counter].roll_no, INPUT_INT);

    /* Get Enrollment Year with validation */
    getValidInput("Please enter the Enrollment year of the student: ",
                  &students[array_counter].enrollment_year, INPUT_INT);

    /* Get Status with validation */
    getValidInput("Please enter the active status of the student (Active/Inactive/Graduated): ",
                  students[array_counter].status, INPUT_STRING);

    /* Get Graduation Year with validation */
    getValidInput("Please enter the graduation year of the student: ",
                  &students[array_counter].graduation_year, INPUT_INT);

    printf("\n\n");

    saveStudentToFile(students[array_counter]);
    array_counter++; // incrementing array counter to the next empty place in the array;
    printf("Student Added Successfully!\n\n");
}

/* ========== Function to display Student data ========== */
void displayStudent(int student_id_search)
{
    int displayed = 0;

#define printData(student)                                            \
    printf("=== Student Data ===\n");                                 \
    printf("Student ID: %d\n", student.student_id);                   \
    printf("Student Name: %s\n", student.name);                       \
    printf("Student Date of Birth: %s\n", student.dob);               \
    printf("Student Gender: %c\n", student.gender);                   \
    printf("Student Current Class: %d\n", student.current_class);     \
    printf("Student Current Section: %c\n", student.section);         \
    printf("Student Roll no.: %d\n", student.roll_no);                \
    printf("Student Enrollment Year: %d\n", student.enrollment_year); \
    printf("Student Status: %s\n", student.status);                   \
    printf("Student Graduation Year: %d\n", student.graduation_year); \
    printf("\n\n");

    for (int i = 0; i < array_counter; i++)
    {
        if (students[i].student_id == student_id_search)
        {
            printData(students[i]);
            displayed = 1;
            break;
        }
    }

    if (displayed != 1)
    {
        Student temp_student;

        FILE *read = fopen("students.dat", "rb");

        while (fread(&temp_student, sizeof(Student), 1, read)) // traverse through the array till we find the matching student id
        {
            if (temp_student.student_id == student_id_search)
            {
                /* Print all the details of the student */
                printData(temp_student);
                displayed = 1;
                break;
            }
        }
        fclose(read);
    }

    if (displayed != 1)
    {
        printf("Student is not present in the records\n");
    }
#undef printData
}

/* ========== Function to save data to a file ========== */
void saveStudentToFile(Student s)
{
    FILE *file = fopen("students.dat", "ab"); // open file pointer to append in the binary file
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fwrite(&students[array_counter], sizeof(Student), 1, file); // write the data to the file
    fclose(file);
}

/* ========== Function to export to a CSV file ========== */
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

    /* Opening the binary file using the read_bin pointer */
    FILE *read_bin = fopen("students.dat", "rb");
    if (!read_bin)
    {
        perror("Error in opening the file: student.dat\n");
        return;
    }

    /* Creating the file with the user input name */
    FILE *write_csv = fopen(input, "w");
    if (!write_csv)
    {
        printf("Error in creating the file: %s\n", input);
        return;
    }

    /* Writing the header of the table */
    fprintf(write_csv, "ID,Name,DOB,Gender,Class,Section,RollNo,EnrollmentYear,Status\n");

    Student s;
    while (fread(&s, sizeof(Student), 1, read_bin))
    {
        fprintf(write_csv, "%d,\"%s\",\"%s\",%c,%d,%c,%d,%d,\"%s\"\n",
                s.student_id, s.name, s.dob, s.gender,
                s.current_class, s.section, s.roll_no,
                s.enrollment_year, s.status);
    }

    printf("\n\nExport successful!!\n\n");
    fclose(read_bin);
    fclose(write_csv);
}

/* ========== Function to delete Student data ========== */
int deleteData(int student_id_to_delete)
{
    while (getchar() != '\n')
        ;
    printf("\n========== Delete Student ==========\n");

    /* Opening the file for reading */
    FILE *read = fopen("students.dat", "rb");
    if (read == NULL)
    {
        perror("Error: Could not open the file for reading\n");
        printf("First Error\n");
        return 1;
    }

    /* Reading the file and calculating the total no. of records in the file */
    fseek(read, 0, SEEK_END);                                      // Traversing from the start to the end to find total no. of bytes
    long file_size = ftell(read);                                  // Finding out the position of the pointer in the file
    unsigned long int total_records = file_size / sizeof(Student); // Calculation total no. of records in the file
    fseek(read, 0, SEEK_SET);                                      // Moving the pointer at the beginning of the file

    /* If the file is empty exit the function */
    if (total_records == 0)
    {
        printf("No records found in the file.\n");
        return 1;
    }

    Student *all_students = malloc(total_records * sizeof(Student)); // Student pointer to temporarily store the data of the file
    if (all_students == NULL)
    {
        perror("Error: Memory allocation failed.\n");
        fclose(read);
        return 1;
    }

    fread(all_students, sizeof(Student), total_records, read); // storing the data from the file int the meomory
    fclose(read);

    int found_index = -1;

    /* Finding the index of the student in the temporary array */
    for (int i = 0; i < total_records; i++)
    {
        if (all_students[i].student_id == student_id_to_delete)
        {
            found_index = i;
            break;
        }
    }

    /* If the student is not present terminate the function */
    if (found_index == -1)
    {
        printf("Student with ID %d not found in the records.\n", student_id_to_delete);
        free(all_students);
        return 1;
    }

    /* Found the student in the records */
    printf("Student found:\n");
    printf("ID: %d \n Name: %s\n",
           all_students[found_index].student_id,
           all_students[found_index].name);

    /* Asking for confirmation from the user for deletion */
    char confirm = 'Z';
    printf("\nAre you sure you want to delete the record of the student? (Y/N): ");
    scanf(" %c", &confirm);
    while (getchar() != '\n')
        ;

    /* If confirmation is not given, terminate the function */
    if (toupper(confirm) != 'Y')
    {
        printf("Deletion cancelled.\n\n");
        free(all_students);
        return 1;
    }

    /* Open a file pointer to write all the records back to the file */
    FILE *file = fopen("students.dat", "wb");
    if (file == NULL)
    {
        perror("Error: Could not open file for writing.\n");
        printf("Second Error\n");
        free(all_students);
        return 1;
    }

    /* Writing the data back to the file */
    for (int i = 0; i < total_records; i++)
    {
        if (i != found_index) // Condition to ignore the student data that the user want to delete
        {
            fwrite(&all_students[i], sizeof(Student), 1, file);
        }
    }

    /* Close the file and free all the memory */
    fclose(file);
    free(all_students);

    /* Delete the record if it is present in the runtime temp array */
    int found_in_array_at_index = -1;
    for (int i = 0; i < array_counter; i++)
    {
        if (students[i].student_id == student_id_to_delete)
        {
            found_in_array_at_index = i;
            break;
        }
    }
    if (found_in_array_at_index == -1)
    {
        printf("The record is only present in the file. Not present in runtime storage.\n");
    }
    else
    {
        for (int i = found_in_array_at_index; i < array_counter - 1; i++)
        {
            students[i] = students[i + 1];
        }
        array_counter--;
    }
    printf("Student data deleted successfully!\n");
}

/* ========== Function to update a Student data ========== */
void updateData(int student_id)
{
    printf("\n=== Update Student ===\n");

    /* Load the file in the memory */
    FILE *read = fopen("students.dat", "rb");
    if (read == NULL)
    {
        perror("Error: Failed to open the file for reading.\n\n");
        return;
    }

    fseek(read, 0, SEEK_END);
    long file_size = ftell(read);
    int total_records = file_size / sizeof(Student);
    fseek(read, 0, SEEK_SET);

    if (total_records == 0)
    {
        printf("No records found.\n\n");
        return;
    }

    Student *all_students = malloc(total_records * sizeof(Student));
    if (all_students == NULL)
    {
        perror("Error: Failed to allocate memory.\n\n");
        return;
    }

    fread(all_students, sizeof(Student), total_records, read);
    fclose(read);

    /* Find the target student record */
    int index = -1;
    for (int i = 0; i < total_records; i++)
    {
        if (all_students[i].student_id == student_id)
        {
            printf("\nStudent Found.\n");
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("\nStudent with ID %d not found in the records.\n", student_id);
        free(all_students);
        return;
    }

    Student *student_found = &all_students[index];

    /* Print the Current data of the student */
    printf("\nCurrent data of the student: %d\nName: %s\nDOB: %s\nGender: %c\nCurrent Class: %d\nSection: %c\nRoll_no: %d\nEnrollment Year: %d\nStatus: %s\nGraduation Year: %d\n",
           student_found->student_id, student_found->name, student_found->dob, student_found->gender,
           student_found->current_class, student_found->section, student_found->roll_no,
           student_found->enrollment_year, student_found->status, student_found->graduation_year);

    /* Ask for confirmation */
    char confirm = 'N';
    printf("\nProceed with update(Y/N): ");
    scanf(" %c", &confirm);
    while (getchar() != '\n')
        ;

    if (toupper(confirm) != 'Y')
    {
        printf("Update cancelled.\n");
        free(all_students);
        return;
    }

    /* If confirmed, prompt for new data */
    getValidInput("\nNew Name: ", &student_found->name, INPUT_STRING);
    getValidInput("New DOB: ", &student_found->dob, INPUT_STRING);
    getValidInput("New Gender: ", &student_found->gender, INPUT_STRING);
    getValidInput("New Class: ", &student_found->current_class, INPUT_INT);
    getValidInput("New Section: ", &student_found->section, INPUT_SECTION);
    getValidInput("New Roll No: ", &student_found->roll_no, INPUT_INT);
    getValidInput("New Enrollment Year: ", &student_found->enrollment_year, INPUT_INT);
    getValidInput("New Status: ", &student_found->status, INPUT_STRING);
    getValidInput("New Graduation year: ", &student_found->graduation_year, INPUT_INT);

    /* Opening the file for writing the data */
    FILE *write = fopen("students.dat", "wb");
    if (write == NULL)
    {
        perror("\nError: Failed to open the file for udpating.\n\n");
        free(all_students);
        return;
    }

    /* Write the updated data into the file */
    fwrite(all_students, sizeof(Student), total_records, write);
    fclose(write);

    /* Sync the runtime array if student record is present */
    for (int i = 0; i < array_counter; i++)
    {
        if (students[i].student_id == student_id)
        {
            students[i] = *student_found;
            break;
        }
    }

    /* Clean up */
    printf("\nRecord Updated Successfully.\n\n");
    free(all_students);
}
