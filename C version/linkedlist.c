#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include "linkedlist.h"

int random_id(void)
{
    int RandIndex = rand() % 999;
    return RandIndex;
}

void main_menu(void)
{
    // Node *head = NULL;
    // Node *tmp = NULL;
    // int choice;

    // system("cls");

    // printf("\n\n\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb HOSTEL MANAGMENT SYSTEM \xdb\xdb\xdb\xdb\xdb\xdb");
    // printf("\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n\n");
    // printf("\t\t\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n\n");
    // printf("<1> Add a new student: \n\n");
    // printf("<2> View all students: \n\n");
    // printf("<3> Search a student: \n\n");
    // printf("<4> Delete a student: \n\n");
    // printf("<5> Update a student: \n\n");
    // printf("<6> Exit Program: \n\n");

    // printf("Choose a number: ");
    // scanf("%d", &choice);

    // switch (choice)
    // {
    // case 1:
    //     system("cls");

    //     tmp = create_student_node();
    //     head = insert_student_node_at_head(head, tmp);

    //     add_student_node_to_file(head);

    //     system("pause");
    //     main_menu();

    //     break;
    // case 2:
    //     system("cls");
    //     Node *new_head_1 = read_students_from_file();
    //     print_list(new_head_1);

    //     system("pause");
    //     main_menu();

    //     break;
    // case 3:
    //     system("cls");
    //     char choice[20];

    //     printf("Find by name or id: ");
    //     scanf("%s", &choice);

    //     if (strcmp(choice, "name") == 0)
    //         find_student_by_name();

    //     if (strcmp(choice, "id") == 0)
    //         find_student_by_id();

    //     else
    //     {
    //         printf("Wrong choice.\nTry again.\n");
    //         system("pause");
    //         main_menu();
    //     }

    //     break;

    // case 4:
    //     system("cls");
    //     char choice1[20];
    //     Node *new_head_2 = read_students_from_file();

    //     printf("Delete student by name or id: ");
    //     scanf("%s", &choice1);

    //     if (strcmp(choice1, "name") == 0)
    //         delete_student_by_name(&new_head_2);

    //     if (strcmp(choice1, "id") == 0)
    //         delete_student_by_id(&new_head_2);

    //     else
    //     {
    //         printf("Wrong choice.\nTry again.\n");
    //         system("pause");
    //         main_menu();
    //     }

    //     break;

    // case 5:
    //     system("cls");
    //     char choice2[20];
    //     Node *new_head_3 = read_students_from_file();

    //     printf("Update student by name or id: ");
    //     scanf("%s", &choice1);

    //     if (strcmp(choice1, "name") == 0)
    //         update_student_by_name(new_head_3);

    //     if (strcmp(choice1, "id") == 0)
    //         update_student_by_id(new_head_3);

    //     else
    //     {
    //         printf("Wrong choice.\nTry again.\n");
    //         system("pause");
    //         main_menu();
    //     }
    //     break;

    // default:
    //     exit(1);
    //     break;
    // }
}

void take_input(char *str)
{
    int ch;
    for (ch = getchar(); isspace(ch); ch = getchar())
        ;

    ungetc(ch, stdin);
    fgets(str, 50, stdin);
}

Node *create_student_node(void)
{
    srand(time(NULL));
    Node *new = malloc(sizeof(Node));
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    new->id = random_id();
    printf("\t\nStudent's ID: %d\n", new->id);

    printf("\t\nEnter a name: ");
    take_input(new->name);

    printf("\t\nEnter an age: ");
    take_input(new->age);

    printf("\t\nEnter an email: ");
    take_input(new->mail_id);

    printf("\t\nEnter a room no.: ");
    take_input(new->room_no);

    printf("\t\nEnter a phone: ");
    take_input(new->phone);

    printf("\t\nEnter a hostel name from BH-1, GH-1, DH-1: ");
    take_input(new->hostel_name);

    strcpy(new->created_at, asctime(tm));
    new->created_at[strlen(new->created_at)] = '\0';
    printf("\t\nCreated at: %s", new->created_at);

    new->next = NULL;
    printf("Student was added.\n\n\n");

    return new;
};

void *find_student_by_name(void)
{
    Node *new_head = read_students_from_file();
    char name[20];
    int found = 1;
    Node *tmp = new_head;

    printf("\nEnter the name: ");
    take_input(name);

    while (strcmp(new_head->name, name) != 0)
        new_head = new_head->next;

    if (new_head == NULL)
    {
        printf("Student not found\n");
        system("pause");
        main_menu();
    }

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

    system("pause");
    main_menu();
}

void *find_student_by_id(void)
{
    Node *new_head = read_students_from_file();
    Node *tmp = new_head;
    int id;

    printf("\nEnter the id: ");
    scanf("%d", &id);

    while (new_head->id != id)
        new_head = new_head->next;

    if (tmp == NULL)
    {
        printf("Student not found\n");
        system("pause");
        main_menu();
    }

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

    system("pause");
    main_menu();
};

void *delete_student_by_name(Node **head)
{
    char name[20];
    Node *tmp = *head;
    Node *curr = *head;
    Node *prev = *head;

    printf("\nEnter the name: ");
    take_input(name);

    if (tmp != NULL && strcmp(tmp->name, name) == 0)
    {
        *head = curr->next;
        free(curr);
        curr = NULL;
        remove("Students.dat");
        add_student_node_to_file(*head);
        printf("Student has been deleted");
        system("pause");
        main_menu();
    }

    while (tmp != NULL && strcmp(tmp->name, name) != 0)
    {
        prev = curr;
        curr = curr->next;
        tmp = tmp->next;
    }

    if (tmp == NULL)
    {
        system("pause");
        main_menu();
    }

    prev->next = curr->next;
    free(curr);
    curr = NULL;
    printf("Student has been deleted.\n");
    remove("Students.dat");
    add_student_node_to_file(*head);
    system("pause");
    main_menu();
}

void *delete_student_by_id(Node **head)
{
    int id;
    Node *tmp = *head;
    Node *curr = *head;
    Node *prev = *head;

    printf("\nEnter the id: ");
    scanf("%d", &id);

    if (tmp != NULL && id == tmp->id)
    {
        printf("Student have been found\n");
        *head = curr->next;
        free(curr);
        curr = NULL;
        remove("Students.dat");
        add_student_node_to_file(*head);
        printf("Student has been deleted\n");
        system("pause");
        main_menu();
    }

    while (tmp != NULL && tmp->id != id)
    {
        prev = curr;
        curr = curr->next;
        tmp = tmp->next;
    }
    if (tmp == NULL)
    {
        system("pause");
        main_menu();
    }
    printf("Student have been found\n");
    prev->next = curr->next;
    free(curr);
    curr = NULL;
    printf("Student has been deleted\n");
    remove("Students.dat");
    add_student_node_to_file(*head);
    system("pause");
    main_menu();
}

void *update_student_by_name(Node *head)
{
    Node *tmp = head;
    char student_name[20];
    char name[60];
    char age[10];
    char mail_id[29];
    char room_no[8];
    char phone[12];
    char hostel_name[8];

    printf("\nEnter the name: ");
    take_input(student_name);

    while (strcmp(tmp->name, student_name) != 0)
        tmp = tmp->next;

    printf("OLD RECORD\n");
    print_list(tmp);

    printf("\t\nNew name: ");
    take_input(name);

    printf("\t\nNew age: ");
    take_input(age);

    printf("\t\nNew email: ");
    take_input(mail_id);

    printf("\t\nNew room no.: ");
    take_input(room_no);

    printf("\t\nNew phone: ");
    take_input(phone);

    printf("\t\nNew hostel name from BH-1, GH-1, DH-1: ");
    take_input(hostel_name);

    strcpy(tmp->name, name);
    strcpy(tmp->age, age);
    strcpy(tmp->mail_id, mail_id);
    strcpy(tmp->room_no, room_no);
    strcpy(tmp->phone, phone);
    strcpy(tmp->hostel_name, hostel_name);

    printf("New RECORD\n");
    print_list(tmp);

    remove("Students.dat");
    add_student_node_to_file(head);

    system("pause");
    main_menu();
}

void *update_student_by_id(Node *head)
{
    Node *tmp = head;
    int student_id;
    char name[60];
    char age[10];
    char mail_id[29];
    char room_no[8];
    char phone[12];
    char hostel_name[8];

    printf("\nEnter the ID: ");
    scanf("%d", &student_id);

    while (tmp->id != student_id)
        tmp = tmp->next;

    printf("OLD RECORD\n");
    print_list(tmp);

    printf("\t\nNew name: ");
    take_input(name);

    printf("\t\nNew age: ");
    take_input(age);

    printf("\t\nNew email: ");
    take_input(mail_id);

    printf("\t\nNew room no.: ");
    take_input(room_no);

    printf("\t\nNew phone: ");
    take_input(phone);

    printf("\t\nNew hostel name from BH-1, GH-1, DH-1: ");
    take_input(hostel_name);

    strcpy(tmp->name, name);
    strcpy(tmp->age, age);
    strcpy(tmp->mail_id, mail_id);
    strcpy(tmp->room_no, room_no);
    strcpy(tmp->phone, phone);
    strcpy(tmp->hostel_name, hostel_name);

    printf("New RECORD\n");
    print_list(tmp);

    remove("Students.dat");
    add_student_node_to_file(head);
    system("pause");
    main_menu();
}

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

        printf("-----------------------------------------------------------------------------------------\n");
        printf("ID: %d \n", tmp->id);
        printf("NAME: %s \n", tmp->name);
        printf("AGE: %s \n", tmp->age);
        printf("EMAIL: %s \n", tmp->mail_id);
        printf("ROOM NUMBER: %s \n", tmp->room_no);
        printf("PHONE: %s \n", tmp->phone);
        printf("HOSTEL NAME: %s \n", tmp->hostel_name);
        printf("CREATED AT: %s \n", tmp->created_at);
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

Node *read_students_from_file(void)
{

    Node *tmp = malloc(sizeof(Node));

    Node *head;
    Node *last;
    last = head = NULL;

    FILE *file = fopen("Students.dat", "r");

    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File'\n");
        printf("Press Enter to Continue...");
        getchar();
        main_menu();
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
