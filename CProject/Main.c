/*  Yvonne Grealy
	G00306806
	Second Year Software Project */

#include "header.h"

main(){

	struct eNode *head=(struct eNode*)malloc(sizeof(struct eNode));
	head->next=NULL;
	readInEmployees(&head);
	

	/*
	
	readInLogin();
	readInEmployees();
	*/
	system("pause");

}//end main

