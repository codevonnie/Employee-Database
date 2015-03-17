#include "header.h"

void readInLogin(){

	if((logPtr = fopen(LOGFILE, "r")) == NULL)
	{
		puts("File could not be opened");
	}

	else
	{
		lhead=(struct node*)malloc(sizeof(struct node));
		lsecond=(struct node*)malloc(sizeof(struct node));
		lthird=(struct node*)malloc(sizeof(struct node));
		fscanf(logPtr, "%s", lhead->login.username);
		fscanf(logPtr, "%s", lhead->login.password);
		
		fscanf(logPtr, "%s", lsecond->login.username);
		fscanf(logPtr, "%s", lsecond->login.password);
		lhead->next=lsecond;
		
		fscanf(logPtr, "%s", lthird->login.username);
		fscanf(logPtr, "%s", lthird->login.password);
		lsecond->next=lthird;
		lthird->next=NULL;
	}
	fclose(logPtr);
	loginSystem();

}//readInLogin

void loginSystem(){

	char c=' ';
	int counter=0, i = 0;
	__check= false;
	
	fflush(stdin);
	printf("Enter username: ");
	scanf("%s", __username);
	printf("**Press Esc to exit**\n");
	printf("Enter password: ");
	//Hide password by replacing letters with *
	while (__check == false){
		c=_getch();
		
		//Esc to exit
		if(c == 27){

			exit(0);
		}
		//Ascii for all allowed charecters 
		else if ((c > 47 && c < 58) || (c>64 && c < 123)){
			__password[i] = c;
			i++;
			printf("*");
		}
		//Allow for character deletion 
		else if (i >= 0 && c == 8){
			i--;
			printf("\b \b");
		}
		
		// Enter key pressed breaks loop
		else if (c == 13){
			__check = true;
		}
	}
	printf("\n\n");
	searchLogin();

}

void readInEmployees(struct eNode *head){

	if((empPtr = fopen(EMPFILE, "rb")) == NULL)
	{
		puts("File could not be opened");
	}

	else{
		

		char data[MAXNUM];
		while(fgets(data, sizeof data, empPtr))
		{
			if(sscanf(data, "%d %[^\,], %[^\,], %[^\,], %d %d %d %f %s", &head->employee.employeeId, head->employee.employeeName, head->employee.employeeAddress, 
				head->employee.department, &head->employee.joined.day, &head->employee.joined.month, &head->employee.joined.year, &head->employee.salary, head->employee.email))
				{
				
				addEmpNode();
				printf("%d %s %s %s %d/%d/%d %.2f %s \n\n", 
					head->employee.employeeId, head->employee.employeeName, head->employee.employeeAddress, head->employee.department, head->employee.joined.day,
					head->employee.joined.month, head->employee.joined.year, head->employee.salary, head->employee.email); 
				}//if
 		}//while
	}
}

void addEmpNode(){

	struct eNode *temp=(struct eNode*)malloc(sizeof(struct eNode));
	struct eNode *newEmp=(struct eNode*)malloc(sizeof(struct eNode));
	temp=head;

	while(temp->next != NULL) // go to the last node
	{
		temp = temp->next;
	}
	
	newEmp->next=NULL;
	temp->next=newEmp; 


}

void searchLogin()
{
	int compName, compPass;
	int iChoice=0;
	struct node *temp; 
	temp =(struct node*)malloc(sizeof(struct node));   
	temp = lhead; 
	
	while( temp!= NULL )
	{
		compName=strcmp(temp->login.username, __username);
		compPass=strcmp(temp->login.password, __password);

		if((compName==0)&&(compPass==0))
		{
			free(lhead);
			readInEmployees();
			while(iChoice!=7){
				switch(iChoice = showMenu())
				{
					case 1:
					{
							addEmployee();
							break;
					}//case1
					case 2:
					{
							displayEmployee();
							break;
					}//case2
					case 3:
					{
							updateEmployee();
							break;
					}//case3
					case 4:
					{
							deleteEmployee();
							break;
					}//case4
					case 5:
					{
							displayByDept();
							break;
					}//case5
					case 6:
					{
							employeeReport();
							break;
					}//case6
					case 7:
					{
							exit(0);
					}//case7
				}//switch
			}//inner while
		}//if 
		temp = temp->next;
	}//while 
	
	printf("\nIncorrect details entered\n");
	loginSystem();
}

int showMenu(){

	int iChoice;
	do
	{
		system("cls");
		printf("\t\t\t\t******************\n\n\t\t\t\t    Employee Database\n\n\t\t\t\t******************\n\n\n");
		printf("\n\n\t\t\t\t 1. Add Employee");
		printf("\n\n\t\t\t\t 2. Display Employee Details");
		printf("\n\n\t\t\t\t 3. Update Employee");
		printf("\n\n\t\t\t\t 4. Delete Employee");
		printf("\n\n\t\t\t\t 5. Display all Employees by Department");
		printf("\n\n\t\t\t\t 6. Display Employee Report");
		printf("\n\n\t\t\t\t 7. Exit");
		printf("\n\n\n\t  Enter a valid option: ");
		scanf("%d", &iChoice);
		fflush(stdin);
	}while( (iChoice < 0) || (iChoice > 8) );

	return(iChoice);
}// end showMenu - ask for user input until number 1-7 is entered

void addEmployee(){}

void displayEmployee(){}

void updateEmployee(){}

void deleteEmployee(){}

void displayByDept(){}

void employeeReport(){}