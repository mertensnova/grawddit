#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct student
{
    int id;
    char name[60];
    char age[10];
    char mail_id[29];
    char room_no[8];
    char phone[12];
    char hostel_name[8];
    char created_at[30];
    struct student *next;

} Node;

void set_time();
Node *insert_student_node_at_head(Node *head, Node *node_to_insert);
void *insert_student_node_at_tail(Node *head, Node *node_to_insert);
void *print_list(Node *head);
void *add_student_node_to_file(Node *head);
Node *create_student_node();
Node *read_students_from_file();
int random_id();
void *find_student_by_name();
void *find_student_by_id();
void *delete_student_by_name(Node **head);
void delete_student_by_id();
char take_input();

#endif
