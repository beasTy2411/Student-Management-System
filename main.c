#include <stdio.h>
#include "functions.c"

int main()
{
    int choice = 0;
    int student_id = 0;
    do
    {
        printf("Welcome to the Student Management System\n");
        printf("1. Add new student data\n");
        printf("2. Display a student data\n");
        printf("3. Delete student data\n");
        printf("9. Export all data to CSV\n");
        printf("0. Exit\n\n");
        printf("Enter a choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            printf("Enter the Student ID: ");
            scanf("%d", &student_id);
            printf("\n\n");
            displayStudent(student_id);
            break;
        case 3:
            printf("Enter the Student ID: ");
            scanf("%d", &student_id);
            deleteData(student_id);
            break;
        case 9:
            exportData();
            break;
        case 0:
            break;
        }

    } while (choice != 0);

    return 0;
}