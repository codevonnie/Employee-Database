#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

#define LOGFILE "login.txt"
#define EMPFILE "employee.txt"
#define MAXNUM 85

typedef int boolean;
#define true 1
#define false 0
boolean __check;

typedef struct login
{
	char username[15];
	char password[6];
}LOG;

struct lNode 
{
	LOG login;
	struct lNode *next;
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
	char email[20];

}EMP;
   
struct node 
{
	EMP employee;
	struct node *next;
};

char __username[15];
char __password[6];
FILE *logPtr;
FILE *empPtr;
	
void readInLogin();
void loginSystem();
void searchLogin(struct lNode **lHead);
struct node readInEmployees(struct node **head);
int showMenu();
void addEmployee(struct node **head);
int displayEmployee(struct node **head);
void findEmployee(struct node **head);
void updateEmployee(struct node **head, int);
void deleteEmployee();
void displayByDept();
void employeeReport();
void displayList(struct node *head);
