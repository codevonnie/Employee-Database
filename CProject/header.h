/*  Yvonne Grealy
	G00306806
	Second Year Advanced Procedural Programming Project */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define LOGFILE "login.txt"
#define EMPFILE "Employees.txt"
#define MAXNUM 100

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

struct date *info;
time_t curtime; // ctime function

typedef struct employee{

	int employeeId;
	char employeeName[30];
	char employeeAddress[40];
	char department[20];
	DATE joined;
	float salary;
	char email[40];

}EMP;
   
struct node{
	EMP employee;
	struct node *next;
};

typedef struct Department{
	
	char departName[20];
	int numOfEmployees;
	float totalSalary;
	float totalBonus;
	float totalOutlay;
}DEPT;

struct dnode{

	DEPT department;
	struct dnode *next;
};

char __username[15];
char __password[6];
FILE *logPtr;
FILE *empPtr;
	
void readInLogin();
void loginSystem();
void searchLogin(struct lNode **lHead);
struct node readInEmployees(struct node *head);
void sort(struct node** head);
int showMenu();
void addEmployee(struct node **head);
int findEmployee(struct node *head);
void displayEmployee(struct node *head, int);
void updateEmployee(struct node **head, int);
void deleteEmployee(struct node **head, int);
void displayByDept(struct node **head);
void employeeReport(struct node *head);
boolean deleteDuplicates(struct dnode **head, struct dnode *newNode);
void writeToFile(struct node *head);
void displayList(struct node *head);