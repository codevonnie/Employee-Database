/*  Yvonne Grealy
	G00306806
	Second Year Software Project */

#include <stdio.h>
#include <stdlib.h>

struct date
{
	int day;
	int month;
	int year;
};

typedef struct date DATE;

struct employee{

	int employeeId;
	char employeeName[30];
	char employeeAddress[40];
	char department[15];
	DATE joined;
	float salary;
	char email[30];

}EMP;
   
typedef struct eNode 
{
	struct EMP;
	struct node *next;
};

int showMenu();
void addEmployee();
void displayEmployee();
void updateEmployee();
void deleteEmployee();
void displayByDept();
void employeeReport();

main(){


}

int showMenu(){}

void addEmployee(){}

void displayEmployee(){}

void updateEmployee(){}

void deleteEmployee(){}

void displayByDept(){}

void employeeReport(){}