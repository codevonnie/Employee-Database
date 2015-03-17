#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define LOGFILE "login.txt"
#define EMPFILE "employee.txt"
#define MAXNUM 80

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

/*typedef struct employeeName{
	 
	char empFirst[15];
	char empLast[15];
}NAME;*/

/*typedef struct employeeAddress{

	int num;
	char fAddress[20];
	char sAddress[20];
}ADDRESS;*/

typedef struct employee{

	int employeeId;
	char employeeName[30];
	char employeeAddress[40];
	char department[15];
	DATE joined;
	float salary;
	char email[20];

}EMP;
   
struct eNode 
{
	EMP employee;
	struct eNode *next;
};

char __username[15];
char __password[6];
struct node *lhead;
struct node *lsecond;
struct node *lthird;
FILE *logPtr;
FILE *empPtr;
	
void readInLogin();
void loginSystem();
void searchLogin();
void readInEmployees(struct eNode **head);
void addEmpNode();
int showMenu();
void addEmployee();
void displayEmployee();
void updateEmployee();
void deleteEmployee();
void displayByDept();
void employeeReport();

