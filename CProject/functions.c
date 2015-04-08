#include "header.h"

void readInLogin(){ //reads in the login credentials from the login file

	
	struct lNode *lHead; //create head for login linkedlist

	if((logPtr = fopen(LOGFILE, "r")) == NULL) //if the file cannot be opened alert the user
	{
		puts("File could not be opened");
	}

	else
	{
		//create linkedlist to hold the login credentials from file
		struct lNode *lSecond;
		struct lNode *lThird;
		lHead=(struct lNode*)malloc(sizeof(struct lNode));
		lSecond=(struct lNode*)malloc(sizeof(struct lNode));
		lThird=(struct lNode*)malloc(sizeof(struct lNode));
		fscanf(logPtr, "%s", lHead->login.username);
		fscanf(logPtr, "%s", lHead->login.password);
		
		fscanf(logPtr, "%s", lSecond->login.username);
		fscanf(logPtr, "%s", lSecond->login.password);
		lHead->next=lSecond;
		
		fscanf(logPtr, "%s", lThird->login.username);
		fscanf(logPtr, "%s", lThird->login.password);
		lSecond->next=lThird;
		lThird->next=NULL;
	}
	fclose(logPtr);
	loginSystem(); //call to loginSystem to print astericks to the screen instead of the password
	searchLogin(lHead); //pass head node to search for the inputed credentials in the saved credentials

}//readInLogin

void loginSystem(){

	char c=' ';
	int counter=0, i = 0;
	__check= false;
	
	fflush(stdin); //flush the standard input
	printf("Enter username: "); 
	scanf("%s", __username); //read in username from user
	printf("**Press Esc to exit**\n");
	printf("Enter password: "); 
	//Hide password by replacing letters with *
	while (__check == false){ //if boolean value check is false...
		c=_getch(); //read in first char
		
		//Esc to exit
		if(c == 27){ //27 is ascii for the ESC key and will allow the user to exit the system

			exit(0);
		}
		//Ascii for all allowed charecters 
		else if ((c > 47 && c < 58) || (c>64 && c < 123)){ //if c is a numeric char or an upper/lowercase letter...
			__password[i] = c; //...position i of the password array is equal to c
			i++; //i is incremented
			printf("*"); //print an asterisk
		}
		//Allow for character deletion 
		else if (i >= 0 && c == 8){ //if backspace key is pressed...
			i--; //...decrement i value
			printf("\b \b");
		}
		
		// Enter key pressed breaks loop
		else if (c == 13){ //13 is ascii code for return key
			__check = true; //set boolean to true to break loop
		}
	}
	printf("\n\n");
}//end loginSystem()

void searchLogin(struct lNode* lHead) //search inputed value with credentials from file
{
	int compName, compPass; //variables to compare username and password
	int iChoice=0;
	struct lNode *temp=(struct lNode*)malloc(sizeof(struct lNode)); //new node created for search
	temp = lHead;  //new node takes value of the head node
	
	while( temp!= NULL ) //while there are still values in the file continue loop
	{
		compName=strcmp(temp->login.username, __username); //compare username input using strcmp and store result
		compPass=strcmp(temp->login.password, __password); //compare password input using strcmp and store result

		if((compName==0)&&(compPass==0)) //if both values are 0 then they are equal and correct
		{
			free(lHead); //free up the space held by login linkedlist
			return; //return when value is found
			
		}//if 
		temp = temp->next; //otherwise go to the next value
	}//while 
	
	printf("\nIncorrect details entered\n"); //if value is not found alert the user
	loginSystem(); //return to the login method to allow user to input details again

}//end searchLogin()

struct node readInEmployees(struct node **head){ //read in employees from employee file

	struct node *temp=(struct node*)malloc(sizeof(struct node)); 
	int count=0;
	temp->next=NULL;
			
	if((empPtr = fopen(EMPFILE, "rb")) == NULL) //if file can not be opened alert the user
	{
		puts("File could not be opened");
	}

	else{

		char data[MAXNUM]; //char array with a max size of 80
		while(fgets(data, sizeof data, empPtr)!=NULL){ //read in from file to char array using file pointer
			struct node *newNode=(struct node*)malloc(sizeof(struct node)); 
			//parse data to the format below and read into new node
			sscanf(data, "%d %[^\,], %[^\,], %[^\,], %d %d %d %f %s", &newNode->employee.employeeId, newNode->employee.employeeName, newNode->employee.employeeAddress, 
			newNode->employee.department, &newNode->employee.joined.day, &newNode->employee.joined.month, &newNode->employee.joined.year, &newNode->employee.salary, 
			newNode->employee.email);
						
			if(count>0){ //if not the first node, set newNode next to temp
				newNode->next=temp;
			}
			else{ //if first node, set newNode next to NULL
				newNode->next=NULL;
			}
			temp=newNode; //temp takes the value of newNode
			count++; //increment count
		}
	}
	*head=temp; //head pointer takes the value of temp
	fclose(empPtr); //close file
	
}//end readInEmployees

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

void addEmployee(struct node** head){ //add employee to linkedlist

	struct node *newEmp=(struct node*)malloc(sizeof(struct node));
	
	//ask user for all employee details and store in newEmp
	printf("\nEnter Employee Number: ");
	scanf("%d", &newEmp->employee.employeeId);
	fflush(stdin);
	printf("\nEnter Employee Name: ");
	scanf("%30[^\n]s", newEmp->employee.employeeName); //continue reading after spaces in name
	fflush(stdin);
	printf("\nEnter Employee Address: ");
	scanf("%40[^\n]s", newEmp->employee.employeeAddress); //continue reading after spaces in address
	fflush(stdin);
	printf("\nEnter Employee Department: ");
	scanf("%15[^\n]s", newEmp->employee.department); //continue reading after spaces in department
	fflush(stdin);
	printf("\nEnter Employee Join Date (dd mm yyyy): ");
	scanf("%d %d %d", &newEmp->employee.joined.day, &newEmp->employee.joined.month, &newEmp->employee.joined.year, 2, 2, 4); //input will be 2 chars, 2 chars and 4 chars to be stored in date struct
	fflush(stdin);
	printf("\nEnter Employee Salary: ");
	scanf("%f", &newEmp->employee.salary);
	fflush(stdin);
	printf("\nEnter Employee email: ");
	scanf("%20s", newEmp->employee.email);

	newEmp->next=*head; //newEmp next points to head pointer
	*head=newEmp; //newEmp is now head

	//print out new employee details
	printf("%d\n %s\n %s\n %s\n %d/%d/%d\n %.2f\n %s \n\n", 
			newEmp->employee.employeeId, newEmp->employee.employeeName, newEmp->employee.employeeAddress, newEmp->employee.department, newEmp->employee.joined.day,
					newEmp->employee.joined.month, newEmp->employee.joined.year, newEmp->employee.salary, newEmp->employee.email); 

	system("pause");


}//end addEmployee()

void displayEmployee(struct node *head){

	char empDetails[30], choice; //employee details to be stored in array
	int compName, empID, count=0;
	struct node *temp=(struct node*)malloc(sizeof(struct node));
	__check=false; //boolean check if emp has been found
	temp=head; //temp struct takes head values
	printf("Enter Employee ID or Name: ");
	scanf("%30[^\n]s", empDetails); //take in employee details from user
	empID=atoi(empDetails); //make int value from user input to check if it is an int value
	
	while((temp!=NULL)&&(__check==false)) //loop while there are still nodes in the linkedlist and while the value has not been found
	{
		compName=strcmp(temp->employee.employeeName, empDetails); //compare employee name with details added by user

		if((compName==0)||(temp->employee.employeeId==empID)){ //if string compare results in 0 or if the id in the current node is equal to user input, print out details
			printf("%d\n %s\n %s\n %s\n %d/%d/%d\n %.2f\n %s \n\n", temp->employee.employeeId, temp->employee.employeeName, temp->employee.employeeAddress,
					temp->employee.department, temp->employee.joined.day, temp->employee.joined.month, temp->employee.joined.year,
						temp->employee.salary, temp->employee.email); 
				__check=true; //change boolean check to true
		}
		else{ //if value not found go to next value in linkedlist
			temp=temp->next;
		}
	}

	if(__check==false){ //if after search check is still false tell the user the employee could not be found

		printf("Employee could not be found");
	}
	
}//displayEmployee()

void updateEmployee(struct node **head){

	struct node *temp=(struct node*)malloc(sizeof(struct node));
	temp=head;


	
}

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

