/*  Yvonne Grealy
	G00306806
	Second Year Software Project */

#include "header.h"

main(){

	lhead=(struct node*)malloc(sizeof(struct node));
	lsecond=(struct node*)malloc(sizeof(struct node));
	lthird=(struct node*)malloc(sizeof(struct node));

	ehead=(struct employee*)malloc(sizeof(struct employee));
	
	//readInLogin();
	readInEmployees();
		
	system("pause");

}//end main

