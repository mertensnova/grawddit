#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

int main(void)
{
    Node *head = NULL;
    Node *tmp = NULL;
    int choice;
    system("cls");

    printf("\t\t\t\t--------------------------- Hostel Managment System -------------------------------\t\n");
    printf("\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb");
    printf("\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n\n");
    printf("\t\t\t\t<1> Add a new student: \n\n");
    printf("\t\t\t\t<2> View all students: \n\n");
    printf("\t\t\t\t<3> Add a new student: \n\n");
    printf("\t\t\t\t<4> Add a new student: \n\n");
    printf("\t\t\t\t<5> Add a new student: \n\n");

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
        Node *new_head = read_students_from_file(head);
        print_list(new_head);
        break;

    default:
        exit(1);
        break;
    }

    return 0;
}
