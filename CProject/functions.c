#include "header.h"

void readInLogin(){

	if((logPtr = fopen(LOGFILE, "r")) == NULL)
	{
		puts("File could not be opened");
	}

	else
	{
		lhead=(struct lNode*)malloc(sizeof(struct lNode));
		lsecond=(struct lNode*)malloc(sizeof(struct lNode));
		lthird=(struct lNode*)malloc(sizeof(struct lNode));
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

void searchLogin()
{
	int compName, compPass;
	int iChoice=0;
	struct lNode *temp=(struct lNode*)malloc(sizeof(struct lNode));   
	temp = lhead; 
	
	while( temp!= NULL )
	{
		compName=strcmp(temp->login.username, __username);
		compPass=strcmp(temp->login.password, __password);

		if((compName==0)&&(compPass==0))
		{
			free(lhead);
			return;
			
		}//if 
		temp = temp->next;
	}//while 
	
	printf("\nIncorrect details entered\n");
	loginSystem();
}

void readInEmployees(struct node **head){

	struct node *temp=(struct node*)malloc(sizeof(struct node));
	
	if((empPtr = fopen(EMPFILE, "rb")) == NULL)
	{
		puts("File could not be opened");
	}

	else{

		char data[MAXNUM];
		while(fgets(data, sizeof data, empPtr))
		{
					
			if(sscanf(data, "%d %[^\,], %[^\,], %[^\,], %d %d %d %f %s", &temp->employee.employeeId, temp->employee.employeeName, temp->employee.employeeAddress, 
				temp->employee.department, &temp->employee.joined.day, &temp->employee.joined.month, &temp->employee.joined.year, &temp->employee.salary, temp->employee.email))
			{
					temp->next=*head;
					*head=temp;
								
					
				/*printf("%d %s %s %s %d/%d/%d %.2f %s \n\n", 
					head->employee.employeeId, head->employee.employeeName, head->employee.employeeAddress, head->employee.department, head->employee.joined.day,
					head->employee.joined.month, head->employee.joined.year, head->employee.salary, head->employee.email); */
			}//if
 		}//while

		fclose(empPtr);
	}
}

int showMenu(){

	int mChoice=0;
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
		printf("\n\n\t\t\t\t 8. Display all Employees");
		printf("\n\n\n\t Enter a valid option: ");
		scanf("%d", &mChoice);
		fflush(stdin);
	}while( (mChoice < 0) || (mChoice > 8) );
	return(mChoice);
		
}// end showMenu - ask for user input until number 1-7 is entered


void addEmployee(struct node** head){

	struct node *newEmp=(struct node*)malloc(sizeof(struct node));
	
	printf("\nEnter Employee Number: ");
	scanf("%d", &newEmp->employee.employeeId);
	fflush(stdin);
	printf("\nEnter Employee Name: ");
	scanf("%30[^\n]s", newEmp->employee.employeeName);
	fflush(stdin);
	printf("\nEnter Employee Address: ");
	scanf("%40[^\n]s", newEmp->employee.employeeAddress);
	fflush(stdin);
	printf("\nEnter Employee Department: ");
	scanf("%15[^\n]s", newEmp->employee.department);
	fflush(stdin);
	printf("\nEnter Employee Join Date (dd mm yyyy): ");
	scanf("%d %d %d", &newEmp->employee.joined.day, &newEmp->employee.joined.month, &newEmp->employee.joined.year, 2, 2, 4);
	fflush(stdin);
	printf("\nEnter Employee Salary: ");
	scanf("%f", &newEmp->employee.salary);
	fflush(stdin);
	printf("\nEnter Employee email: ");
	scanf("%20s", newEmp->employee.email);

	newEmp->next=*head;
	*head=newEmp;

	printf("%d\n %s\n %s\n %s\n %d/%d/%d\n %.2f\n %s \n\n", 
			newEmp->employee.employeeId, newEmp->employee.employeeName, newEmp->employee.employeeAddress, newEmp->employee.department, newEmp->employee.joined.day,
					newEmp->employee.joined.month, newEmp->employee.joined.year, newEmp->employee.salary, newEmp->employee.email); 

	system("pause");


}//end addEmployee()

void displayEmployee(struct node *head){

	char empDetails[30];
	int empID;
	char c;
	struct node *temp=(struct node*)malloc(sizeof(struct node));
	__check=false;
	temp=head;
	printf("Enter Employee ID or Name: ");
	scanf("%30[^\n]s", empDetails);
	c=empDetails[0];

	if(isdigit(c)){
		
		empID=(int)empDetails;

		while(temp!=NULL){

			if(temp->employee.employeeId==empID){

				printf("%d\n %s\n %s\n %s\n %d/%d/%d\n %.2f\n %s \n\n", temp->employee.employeeId, temp->employee.employeeName, temp->employee.employeeAddress,
					temp->employee.department, temp->employee.joined.day, temp->employee.joined.month, temp->employee.joined.year,
						temp->employee.salary, temp->employee.email); 
				__check=true;
			}//nested if1

			temp=temp->next;
		}//while1
	}//if
	else if((!(isdigit(c)))&&(__check==false)){
		while(temp!=NULL){

			if(temp->employee.employeeId==empDetails){

				printf("%d\n %s\n %s\n %s\n %d/%d/%d\n %.2f\n %s \n\n", temp->employee.employeeId, temp->employee.employeeName, temp->employee.employeeAddress,
					temp->employee.department, temp->employee.joined.day, temp->employee.joined.month, temp->employee.joined.year,
						temp->employee.salary, temp->employee.email); 
				__check=true;
			}//nested if2

			temp=temp->next;

		}//while2
	}//else if
	else if(__check==false){

		printf("Employee could not be found");
	}
}//displayEmployee()

void updateEmployee(){}

void deleteEmployee(){}

void displayByDept(){}

void employeeReport(){}

void displayList(struct node* head){

	struct node *temp; 
	temp =(struct node*)malloc(sizeof(struct node)); 
	temp = head; 
	while( temp!= NULL )
	{
		printf("%d\n %s\n %s\n %s\n %d/%d/%d\n %.2f\n %s \n\n", temp->employee.employeeId, temp->employee.employeeName, temp->employee.employeeAddress,
					temp->employee.department, temp->employee.joined.day, temp->employee.joined.month, temp->employee.joined.year,
						temp->employee.salary, temp->employee.email); 
		temp = temp->next; 
	}
}