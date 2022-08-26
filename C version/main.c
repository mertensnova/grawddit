#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

int main(void)
{
    Node *head = NULL;
    Node *tmp = NULL;
    // Node *new_head = read_students_from_file();
    int choice;

    system("cls");

    printf("\t\t\t\t--------------------------- Hostel Managment System -------------------------------\t\n");
    printf("\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb");
    printf("\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n\n");
    printf("\t\t\t\t<1> Add a new student: \n\n");
    printf("\t\t\t\t<2> View all students: \n\n");
    printf("\t\t\t\t<3> Search a student: \n\n");
    printf("\t\t\t\t<4> Delete a student: \n\n");
    printf("\t\t\t\t<5> Update a student: \n\n");
    printf("\t\t\t\t<6> Exit Program: \n\n");

    printf("\t\t\t\tChoose a number: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        system("cls");

        tmp = create_student_node();
        head = insert_student_node_at_head(head, tmp);

        add_student_node_to_file(head);
        break;
    case 2:
        system("cls");
        Node *new_head_1 = read_students_from_file();
        print_list(new_head_1);
        break;
    case 3:
        system("cls");
        char choice[20];

        printf("Find by name or id: ");
        scanf("%s", &choice);

        if (strcmp(choice, "name") == 0)
            find_student_by_name();

        if (strcmp(choice, "id") == 0)
            find_student_by_id();

        break;

    case 4:
        system("cls");
        char choice1[20];
        Node *new_head_2 = read_students_from_file();

        printf("Delete student by name or id: ");
        scanf("%s", &choice1);

        if (strcmp(choice1, "name") == 0)
            delete_student_by_name(&new_head_2);

        if (strcmp(choice1, "id") == 0)
            delete_student_by_id(&new_head_2);
        break;

    case 5:
        system("cls");
        char choice2[20];
        Node *new_head_3 = read_students_from_file();

        printf("Updatestudent by name or id: ");
        scanf("%s", &choice1);

        if (strcmp(choice1, "name") == 0)
            update_student_by_name(new_head_3);

        if (strcmp(choice1, "id") == 0)
            update_student_by_id(new_head_3);
        break;

    default:
        exit(1);
        break;
    }

    return 0;
}
