#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct student
{
    int id;
    int age;
    char name[60];
    char mail_id[19];
    char room_no[8];
    char phone[12];
    char hostel_name[8];
    struct student *next;

} Node;

Node *create_student_node(
    int id,
    int age,
    char *name,
    char *mail_id,
    char *room_no,
    char *phone,
    char *hostel_name);

Node *insert_student_node_at_head(Node *head, Node *node_to_insert);

void *print_list(Node *head);

void *add_student_node_to_file(Node *head);

Node *read_students_from_file();

#endif
