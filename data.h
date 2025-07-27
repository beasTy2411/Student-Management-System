#ifndef DATA_H_
#define DATA_H_

// A data structure to contain the information of a student
typedef struct Student
{
    int student_id;      // Unique Student Id
    char name[30];       // Student name
    char dob[11];        // Student Date of Birth (DD-MM-YYYY)
    char gender;         // Student Gender
    int current_class;   // Student Current Class (In decimal: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11,12)
    char section;        // Student Current Class Section (In alphabet - A, B, C, D)
    int roll_no;         // Student Current Class Roll no.
    int enrollment_year; // Student Admission Year in School
    char status[10];     // Student Current Status (Active, Inactive, Graduated)
    int graduation_year; // Student Graduation year
} Student;

typedef enum
{
    INPUT_INT,
    INPUT_STRING,
    INPUT_GENDER,
    INPUT_SECTION
} InputType;

// external global variables
extern Student students[100]; // Array of student data type;; currently of size 100 but will improve it in future;;
extern int array_counter;     // a counter to check the current position in the array

// function prototypes
void getValidInput(const char *prompt, void *destination, InputType type); // validates the input
void addStudent();                                                         // to add data of a new student
void displayStudent(int student_id_search);                                // search a student based on the student_id provided and print the data
void saveStudentToFile(Student s);                                         // write the input taken from user into a file
void exportData();                                                         // export teh data from the binary file to a csv file
int deleteData(int student_id);                                           // search for the student with the entered id and delete it

#endif