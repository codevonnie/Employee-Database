/*  Yvonne Grealy
	G00306806
	Second Year Software Project */

#include "header.h"

main(){

	int mChoice=0;
	struct node *head=(struct node*)malloc(sizeof(struct node));
	head->next=NULL;
	readInLogin();
	readInEmployees(&head);
		
	while(mChoice!=7){
		switch(mChoice = showMenu())
		{
			case 1:
			{
				addEmployee(&head);
				break;
			}//case1
			case 2:
			{
				displayEmployee(head);
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
			case 8:
			{
				displayList(head);
				break;
			}
		}//switch
	}//inner while
	
	system("pause");

}//end main

