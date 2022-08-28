#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include "linkedlist.h"

int main(void)
{
    FILE *fp;
    fp = fopen("Students.dat", "w");
    Node *head = NULL;
    Node *tmp = NULL;
    Node *new_head;
    int choice;

    printf("\t\t\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n\n");
    printf("<1> Add a new student: \n\n");
    printf("<2> View all students: \n\n");
    printf("<3> Search a student: \n\n");
    printf("<4> Delete a student: \n\n");
    printf("<5> Update a student: \n\n");
    printf("<6> Exit Program: \n\n");

    printf("Choose a number: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
    {
        tmp = create_student_node();
        head = insert_student_node_at_head(head, tmp);

        add_student_node_to_file(head);

        system("pause");
        main_menu();
    }

    break;
    case 2:
    {
        new_head = read_students_from_file();
        print_list(new_head);

        system("pause");
        main_menu();
    }

    break;
    case 3:

    {
        char choice[20];

        printf("Find by name or id: ");
        scanf("%s", &choice);

        if (strcmp(choice, "name") == 0)
            find_student_by_name();

        if (strcmp(choice, "id") == 0)
            find_student_by_id();

        else
        {
            printf("Wrong choice.\nTry again.\n");
            system("pause");
            main_menu();
        }
    }
    break;

    case 4:
    {
        char choice[20];
        new_head = read_students_from_file();

        printf("Delete student by name or id: ");
        scanf("%s", &choice);

        if (strcmp(choice, "name") == 0)
            delete_student_by_name(&new_head);

        if (strcmp(choice, "id") == 0)
            delete_student_by_id(&new_head);

        else
        {
            printf("Wrong choice.\nTry again.\n");
            system("pause");
            main_menu();
        }
    }
    break;

    case 5:

    {
        char choice[20];
        new_head = read_students_from_file();

        printf("Update student by name or id: ");
        scanf("%s", &choice);

        if (strcmp(choice, "name") == 0)
            update_student_by_name(new_head);

        if (strcmp(choice, "id") == 0)
            update_student_by_id(new_head);

        else
        {
            printf("Wrong choice.\nTry again.\n");
            system("pause");
            main_menu();
        }
    }
    break;

    default:
        exit(1);
        break;
    }
    return 0;
}
