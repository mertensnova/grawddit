#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "linked_list.h"

int random_id()
{
    srand(time(NULL));
    int RandIndex = rand() % 999;
    return RandIndex;
}

Node *create_student_node()
{
    Node *new = malloc(sizeof(Node));
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    new->id = random_id();
    printf("\t\nEnter an ID: %d ", new->id);

    printf("\t\nEnter a name: ");
    fgets(new->name, 50, stdin);
    new->name[strlen(new->name) - 1] = '\0';

    printf("\t\nEnter an age: ");
    fgets(new->age, 50, stdin);
    new->age[strlen(new->age) - 1] = '\0';

    printf("\t\nEnter an email: ");
    fgets(new->mail_id, 50, stdin);
    new->mail_id[strlen(new->mail_id) - 1] = '\0';

    printf("\t\nEnter a room no.: ");
    fgets(new->room_no, 50, stdin);
    new->room_no[strlen(new->room_no) - 1] = '\0';

    printf("\t\nEnter a phone: ");
    fgets(new->phone, 50, stdin);
    new->phone[strlen(new->phone) - 1] = '\0';

    printf("\t\nEnter a hostel name from BH-1, GH-1, DH-1: ");
    fgets(new->hostel_name, 50, stdin);
    new->hostel_name[strlen(new->hostel_name) - 1] = '\0';

    strcpy(new->created_at, asctime(tm));
    new->created_at[strlen(new->created_at) - 1] = '\0';
    printf("\t\nCreated at: %s", new->created_at);

    new->next = NULL;

    return new;
};

Node *insert_student_node_at_head(Node *head, Node *node_to_insert)
{
    node_to_insert->next = head;
    return node_to_insert;
}

void *insert_student_node_at_tail(Node *head, Node *node_to_insert)
{
    Node *tmp = head;
    while (tmp->next != NULL)
        tmp = tmp->next;

    tmp->next = node_to_insert;
}

void *print_list(Node *head)
{
    Node *tmp = head;

    while (tmp != NULL)
    {
        printf("--------------------------------------------------------------\n");
        printf("id:%d \n", tmp->id);
        printf("Name:%s \n", tmp->name);
        printf("Age:%d \n", tmp->age);
        printf("Email:%s \n", tmp->mail_id);
        printf("Room no.:%s \n", tmp->room_no);
        printf("Phone number:%s \n", tmp->phone);
        printf("Hostel name:%s \n", tmp->hostel_name);
        tmp = tmp->next;
    }
}

void *add_student_node_to_file(Node *head)
{
    Node *tmp = head;
    FILE *file = fopen("Students.dat", "ab");

    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File'\n");
        exit(1);
    }

    while (tmp != NULL)
    {
        fwrite(tmp, sizeof(Node), 1, file);
        tmp = tmp->next;
    }

    fclose(file);
}

Node *read_students_from_file()
{

    Node *tmp = malloc(sizeof(Node));

    Node *head;
    Node *last;
    last = head = NULL;

    FILE *file = fopen("Students.dat", "rb");

    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File'\n");
        exit(1);
    }

    while (fread(tmp, sizeof(Node), 1, file))
    {
        if (head == NULL)
            head = last = malloc(sizeof(Node));
        else
        {
            last->next = malloc(sizeof(Node));
            last = last->next;
        }

        // last->id = tmp->id;
        // last->age = tmp->age;
        strcpy(last->name, tmp->name);
        strcpy(last->mail_id, tmp->mail_id);
        strcpy(last->room_no, tmp->room_no);
        strcpy(last->phone, tmp->phone);
        strcpy(last->hostel_name, tmp->hostel_name);

        last->next = NULL;
    }

    fclose(file);

    return head;
}
