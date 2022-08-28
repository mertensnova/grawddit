#ifndef LINKEDLIST_H
#define LINKEDLIST_H

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

int random_id(void);
void take_input(char *str);
void *insert_student_node_at_tail(Node *head, Node *node_to_insert);
void *print_list(Node *head);
void *add_student_node_to_file(Node *head);
void *find_student_by_name(void);
void *find_student_by_id(void);
void *delete_student_by_name(Node **head);
void *delete_student_by_id(Node **head);
void *update_student_by_name(Node *head);
void *update_student_by_id(Node *head);
Node *read_students_from_file(void);
Node *create_student_node(void);
Node *insert_student_node_at_head(Node *head, Node *node_to_insert);

#endif
