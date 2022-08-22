#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

Node *create_student_node(
    int id,
    int age,
    char *name,
    char *mail_id,
    char *room_no,
    char *phone,
    char *hostel_name)
{
    Node *new = malloc(sizeof(Node));
    new->id = id;
    new->age = age;
    strcpy(new->name, name);
    new->name[60 - 1] = '\0';
    strcpy(new->mail_id, mail_id);
    new->mail_id[30 - 1] = '\0';
    strcpy(new->room_no, room_no);
    new->room_no[8 - 1] = '\0';
    strcpy(new->phone, phone);
    new->phone[12 - 1] = '\0';
    strcpy(new->hostel_name, hostel_name);
    new->hostel_name[6 - 1] = '\0';
    new->next = NULL;

    return new;
};

Node *insert_student_node_at_head(Node *head, Node *node_to_insert)
{
    node_to_insert->next = head;
    return node_to_insert;
}

void *print_list(Node *head)
{
    Node *tmp = head;

    while (tmp != NULL)
    {
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

        last->id = tmp->id;
        last->age = tmp->age;
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

// void *add_student_node()
// {
//     Node *new = malloc(sizeof(Node));
//     // printf("Enter an id: \n");
//     // scanf("%d", &new->id);
//     // printf("Enter a name: \n");
//     // fgets(new->name, 60, stdin);
//     // printf("Enter an age: \n");
//     // scanf("%d", &new->age);
//     // printf("Enter a city: \n");
//     // fgets(new->city, 60, stdin);
//     // printf("Enter an email: \n");
//     // fgets(new->mail_id, 60, stdin);
//     // printf("Enter a room no.: \n");
//     // fgets(new->room_no, 60, stdin);
//     // printf("Enter a phone: \n");
//     // fgets(new->phone, 60, stdin);
//     // printf("Enter a hostel name from BH-1, GH-1, DH-1: \n");
//     // fgets(new->hostel_name, 60, stdin);
//     // new->next = NULL;
// }
