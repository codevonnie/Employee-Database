/*  Yvonne Grealy
	G00306806
	Second Year Advanced Procedural Programming Project */

#include "header.h"

main(){

	int mChoice=0; //holds user choice of menu options
	struct node *head=(struct node*)malloc(sizeof(struct node));//create head node for employees
	head->next=NULL; //set head next to null 
	//readInLogin(); //call login method
	readInEmployees(&head); //head takes the head value from this method which reads in employees from file
		
	while(mChoice!=7){ //while choice does not equal the exit value 7
		switch(mChoice = showMenu()) 
		{
			case 1: 
			{
				addEmployee(&head);//add an employee to the database
				break;
			}//case1
			
			case 2:
			{
				displayEmployee(head); //display a chosen employees details
				break;
			}//case2
			case 3:
			{
				updateEmployee(); //update details for a chosen employee
				break;
			}//case3
			case 4:
			{
				deleteEmployee(); //delete a chosen employee
				break;
			}//case4
			case 5:
			{
				displayByDept(); //display all employees by their department
				break;
			}//case5
			case 6:
			{
				employeeReport(); //displays employee report
				break;
			}//case6
			case 7:
			{
				exit(0); //exit the program
			}//case7
			
			case 8: //TEST CASE TO BE DELETED
			{
				displayList(head); 
				system("pause");
				break;
			}
		}//switch
 	}//inner while
	
	system("pause");

}//end main

