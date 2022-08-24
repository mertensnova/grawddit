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
    printf("\t\nEnter an ID: %d\n", new->id);

    printf("\t\nEnter a name: ");
    getchar();
    fgets(new->name, 50, stdin);
    new->name[strlen(new->name) - 1] = '\0';

    printf("\t\nEnter an age: ");
    getchar();
    fgets(new->age, 50, stdin);
    new->age[strlen(new->age) - 1] = '\0';

    printf("\t\nEnter an email: ");
    getchar();
    fgets(new->mail_id, 50, stdin);
    new->mail_id[strlen(new->mail_id) - 1] = '\0';

    printf("\t\nEnter a room no.: ");
    getchar();
    fgets(new->room_no, 50, stdin);
    new->room_no[strlen(new->room_no) - 1] = '\0';

    printf("\t\nEnter a phone: ");
    getchar();
    fgets(new->phone, 50, stdin);
    new->phone[strlen(new->phone) - 1] = '\0';

    printf("\t\nEnter a hostel name from BH-1, GH-1, DH-1: ");
    getchar();
    fgets(new->hostel_name, 50, stdin);
    new->hostel_name[strlen(new->hostel_name) - 1] = '\0';

    strcpy(new->created_at, asctime(tm));
    new->created_at[strlen(new->created_at) - 1] = '\0';
    printf("\t\nCreated at: %s", new->created_at);

    new->next = NULL;

    printf("\t\n%s was added successfully", new->name);

    return new;
};

void *find_student_by_name()
{
    Node *new_head = read_students_from_file();
    char name[20];

    printf("\nEnter the name: ");
    getchar();
    fgets(name, 30, stdin);
    name[strlen(name) - 1] = '\0';

    while (strcmp(new_head->name, name) != 0)
        new_head = new_head->next;

    printf("Student Found\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("ID: %d\n", new_head->id);
    printf("Name:%s \n", new_head->name);
    printf("Age:%s \n", new_head->age);
    printf("Email:%s \n", new_head->mail_id);
    printf("Room Number:%s \n", new_head->room_no);
    printf("Phone:%s \n", new_head->phone);
    printf("Hostel Name:%s \n", new_head->hostel_name);
    printf("Created At:%s \n", new_head->created_at);
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

        printf("\tID\tName\tAge\tEmail\tRoom No.\tPhone\tHostel Name\tCreated At\n");
        printf("-----------------------------------------------------------------------------------------\n");
        printf("%9d", tmp->id);
        printf("%9s", tmp->name);
        printf("%9s", tmp->age);
        printf("%9s", tmp->mail_id);
        printf("%9s", tmp->room_no);
        printf("%9s", tmp->phone);
        printf("%9s", tmp->hostel_name);
        printf("%9s", tmp->created_at);
        tmp = tmp->next;
    }
}

void *add_student_node_to_file(Node *head)
{
    Node *tmp = head;
    FILE *file = fopen("Students.dat", "a");

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

    FILE *file = fopen("Students.dat", "r");

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
        strcpy(last->name, tmp->name);
        strcpy(last->age, tmp->age);
        strcpy(last->mail_id, tmp->mail_id);
        strcpy(last->room_no, tmp->room_no);
        strcpy(last->phone, tmp->phone);
        strcpy(last->hostel_name, tmp->hostel_name);
        strcpy(last->created_at, tmp->created_at);

        last->next = NULL;
    }

    fclose(file);

    return head;
}
