/*  Yvonne Grealy
	G00306806
	Second Year Software Project */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void logInMenu();
void search_list(struct node* head);
int showMenu();
void addEmployee();
void displayEmployee();
void updateEmployee();
void deleteEmployee();
void displayByDept();
void employeeReport();

typedef int boolean;
#define true 1
#define false 0
boolean __check;

typedef struct login
{
	char username[15];
	char password[6];
}LOG;

struct node 
{
	LOG login;
	struct node *next;
};

typedef struct date
{
	int day;
	int month;
	int year;
}DATE;

typedef struct employee{

	int employeeId;
	char employeeName[30];
	char employeeAddress[40];
	char department[15];
	DATE joined;
	float salary;
	char email[30];

}EMP;
   
struct eNode 
{
	EMP emp;
	struct node *next;
};

char __username[15];
char __password[6];




void display_list(struct node* head);


main(){

	FILE *lPtr;

	struct node *head;
	struct node *second;
	struct node *third;

	head=(struct node*)malloc(sizeof(struct node));
	second=(struct node*)malloc(sizeof(struct node));
	third=(struct node*)malloc(sizeof(struct node));
	
	if((lPtr = fopen("login.txt", "r")) == NULL)
	{
		puts("File could not be opened");
	}

	else
	{
		fscanf(lPtr, "%s", head->login.username);
		fscanf(lPtr, "%s", head->login.password);
		
		fscanf(lPtr, "%s", second->login.username);
		fscanf(lPtr, "%s", second->login.password);
		head->next=second;
		
		fscanf(lPtr, "%s", third->login.username);
		fscanf(lPtr, "%s", third->login.password);
		second->next=third;
		third->next=NULL;
	}

	logInMenu();
	display_list(head);
	search_list(head);
		

	system("pause");

}//end main

void logInMenu(){

	char c=' ';
	int counter=0, i = 0;
	__check= false;

	fflush(stdin);
	printf("Enter username: ");
	scanf("%s", __username);
	printf("Enter password: ");
	//Replacing * instead of the password
	while (__check == false){
		c=_getch();
		//Ascii for all allowd charecters 
		if ((c > 47 && c < 58) || (c>64 && c < 123)){
			__password[i] = c;
			i++;
			printf("*");
		}
		//code for backspaces 
		else if (i >= 0 && c == 8){
			i--;
			printf("\b \b");
		}
		// ASCII 13 = Enter key
		else if (c == 13){
			__check = true;
		}
	}
	printf("\n\n");

}

void search_list(struct node* head)
{
	struct node *temp; 
	temp =(struct node*)malloc(sizeof(struct node));   
	temp = head; 
	int compName; 
	int compPass;
	while( temp!= NULL )
	{
		compName=strcmp(temp->login.username, __username);
		compPass=strcmp(temp->login.password, __password);

		if((compName==0)&&(compPass==0))
		{
			printf("\nData Found.");
			return;
		} 
			temp = temp->next;
	}//while 
	
	printf("\nData not found");
}

void display_list(struct node* head){

	struct node *temp; 
	temp =(struct node*)malloc(sizeof(struct node)); 
	temp = head; 
	while( temp!= NULL )
	{
		printf("Username: %s Password: %s\n", temp->login.username, temp->login.password); // show the data 
		temp = temp->next; 
	}
}


int showMenu(){}

void addEmployee(){}

void displayEmployee(){}

void updateEmployee(){}

void deleteEmployee(){}

void displayByDept(){}

void employeeReport(){}