#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

int main()
{
    Node *head = NULL;
    Node *tmp = NULL;

    // for (int i = 0; i < 25; i++)
    // {
    //     tmp = create_student_node(i, 12, "John", "john@gmail.com", "1231", "123123123", "BH-1");
    //     head = insert_student_node_at_head(head, tmp);
    // }

    // add_student_node_to_file(head);

    Node *newHead = read_students_from_file();
    print_list(newHead);

    return 0;
}
