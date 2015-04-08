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

int findEmployee(struct node *head){

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
			
				__check=true; //change boolean check to true
				return count;
		}
		else{ //if value not found go to next value in linkedlist
			temp=temp->next;
		}
		count++;
	}

	if(__check==false){ //if after search check is still false tell the user the employee could not be found

		printf("\n\n\t\t********Employee could not be found********\n\n");
		count=-1;
	}
	system("pause");
	return count;
	
}//findEmployee()

void displayEmployee(struct node *head, int count){ //display employee details if employee was found in previous method

	struct node *temp=(struct node*)malloc(sizeof(struct node));
	int i;
	temp=head; //temp takes values of head

	for(i=0; i<count;i++){ //loop goes to the node that was found to contain employee in prev method
		temp=temp->next;
	}
	//print out emp details to user
	printf("%d\n %s\n %s\n %s\n %d/%d/%d\n %.2f\n %s \n\n", temp->employee.employeeId, temp->employee.employeeName, temp->employee.employeeAddress,
	temp->employee.department, temp->employee.joined.day, temp->employee.joined.month, temp->employee.joined.year,
	temp->employee.salary, temp->employee.email);
		
	system("pause");

}//end displayEmployee

void updateEmployee(struct node **head, int count){ //update employee as selected by user using count from findEmployee method

	struct node *temp=(struct node*)malloc(sizeof(struct node));
	int i;
	char choice=' ';
	__check=false;
	temp=*head; //temp gets pointer address for head of linkedlist

	for(i=0; i<count;i++){//loop goes to the node that was found to contain employee in prev method
		temp=temp->next;
	}
	
	while(__check==false){ //while check is false continue looping

		//print out selected employee
		printf("%d\n %s\n %s\n %s\n %d/%d/%d\n %.2f\n %s \n\n", temp->employee.employeeId, temp->employee.employeeName, temp->employee.employeeAddress,
		temp->employee.department, temp->employee.joined.day, temp->employee.joined.month, temp->employee.joined.year,
		temp->employee.salary, temp->employee.email);
		
		printf("Do you wish to change employee Address, Department or Salary? (e to exit)");
		scanf(" %c", &choice); //get user to input which detail they wish to change or e to exit
		fflush(stdin); //flush buffer

		switch(choice)//using user choice
		{
			case 'a':
			case 'A': //upper or lowercase A for address
				{
						printf("Please enter amended address: ");
						scanf("%40[^\n]s", &temp->employee.employeeAddress); //get input of amended address and overwrite previous employee address in node
						__check=true; //set check to true
						break; //break from switch
				}
			case 'd':
			case 'D': //upper or lowercase D for department
				{	
						printf("Please enter amended department: ");
						scanf("%15[^\n]s", &temp->employee.department); //get input of amended department and overwrite previous employee department in node
						__check=true; //set check to true
						break; //break from switch
				}
			case 's':
			case 'S':
				{
						printf("Please enter emended salary: ");
						scanf("%f", &temp->employee.salary); //get input of amended salary and overwrite previous employee salary in node
						__check=true; //set check to true
						break; //break from switch
				}
			case 'e':
			case 'E':
				{
						return; //exit method if user enters upper or lowercase E
				}
			default:
				{		//tell the user if they input an invalid entry and loop back over the while loop
						printf("\n\n\t\t********Sorry that is not a valid option********\n\n");
					
				}

		}//end switch
	}//end while
	printf("Employee details updated successfully\n\n"); //confirm that the user has amended the details
	system("pause");
}//updateEmployee

void deleteEmployee(struct node **head, int count){ //delete employee inputted by user and found in findEmployee method

	struct node *temp1=(struct node*)malloc(sizeof(struct node)); 
	struct node *temp2=(struct node*)malloc(sizeof(struct node)); 
	int i;
	temp1 = *head; //temp1 gets address of head of linkedlist
	if(count==0){ //if the node to be deleted is at the start of the linkedlist use this code
		*head=temp1->next; //head points to the value pointed to by temp1
		free(temp1); //temp1 is freed from memory
		printf("Employee deleted\n\n"); //confirm to user that employee has been deleted
		system("pause");
		return; //exit method
	}
	 
	for(i=0; i<count-1;i++){ //if it is not the first node that is required use loop to get to the node before the node to be deleted
		temp1=temp1->next;
	}

	temp2=temp1->next; //temp2 takes value of the node for deletion
	temp1->next=temp2->next; //temp1 now points to what temp2 used to point to
	free(temp2); //temp2 is freed from memory

	printf("Employee deleted\n\n");//confirm to user that employee has been deleted
	system("pause");

}//deleteEmployee

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

